//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "OptEngine.h"
#include <omnetpp.h>
#include <fstream>
#include <map>
#include <FindModule.h>
#include <BaseBattery.h>
#include "StaticNetwLayer.h"
#include "IDSSimpleLayer.h"

Define_Module(OptEngine);
using namespace std;

/**
 * Initialize module
 */
void OptEngine::initialize(int stage){
	BaseModule::initialize(stage);
	if (stage==0) {
		// get global network module
		network = FindModule<>::findNetwork(this);
		// get debug switch
		debug = par("debug").boolValue();
		// get simulation time limit from configuration
		simtimelimit = atof(ev.getConfig()->getConfigValue("sim-time-limit"));
		// create timer for publishing current progress of simulation
		fractionDoneTimer = new cMessage("fractionDone", FRACTION_DONE_TIMER);
	} else if (stage==1) {
		if (simtimelimit>0)
			scheduleAt(simTime(), fractionDoneTimer);
	}
}

OptEngine::~OptEngine(){
	cancelAndDelete(fractionDoneTimer);
}

void OptEngine::handleMessage(cMessage *msg){

	switch (msg->getKind()) {
		case FRACTION_DONE_TIMER: {
			ofstream ofstr (par("fractionDoneFile"));
			if (ofstr.is_open()){
				ofstr.precision(4);
				ofstr << (simTime()/simtimelimit);
				ofstr.close();
			}
			scheduleAt(simTime() + simtimelimit/100, fractionDoneTimer);
			break;
		}
		default:
			EV<< "Unkown selfmessage! -> delete, kind: " << msg->getKind() << endl;
			delete msg;
			break;
	}
}

/**
 * Finish and compute neccessary metrics
 */
void OptEngine::finish(){

	// Start with false negatives and false positives
	cModule* node;
	IDSSimpleLayer* ids;
	StaticNetwLayer* netw;

	map<unsigned int, bool> isAttacker;
	map<unsigned int, bool> detectedAsAttacker;

	// Get all attackers
	unsigned int nodeID = 0;
	do {
		node = network->getSubmodule("node", nodeID);
		ids = node!=NULL?FindModule<IDSSimpleLayer*>::findSubModule(node):NULL;
		netw = node!=NULL?FindModule<StaticNetwLayer*>::findSubModule(node):NULL;

		if (netw != NULL){
			isAttacker[nodeID] = netw->pPacketDropping>0;
		}

		nodeID++;
	} while (node);

	// Compute detection stats for all thresholds
	map<double, IDSStats> thresholdStats;
	for (double threshold=0; threshold<1.01; threshold+=0.01){
		nodeID = 0;

		// clear detection stats
		for (map<unsigned int, bool>::iterator it = detectedAsAttacker.begin(); it != detectedAsAttacker.end(); it++)
			detectedAsAttacker[it->first] = false;

		do {
			node = network->getSubmodule("node", nodeID);
			ids = node!=NULL?FindModule<IDSSimpleLayer*>::findSubModule(node):NULL;
			netw = node!=NULL?FindModule<StaticNetwLayer*>::findSubModule(node):NULL;

			if (ids != NULL && netw != NULL){
				for (IDSMap::iterator it=ids->forwardersMap.begin();it!=ids->forwardersMap.end();it++){
					IDSEntry* entry = &(it->second);
					const int nodeAddr = it->first;

					// ignore neighbors that received less than fwdMinPacketsReceived packets
					if (entry->packetsReceived < ids->fwdMinPacketsReceived)
						continue;

					// update detection stats
					if (entry->getPacketsDroppedRatio() >= threshold){
						detectedAsAttacker[nodeAddr] = true;

						if (isAttacker[nodeAddr])
							thresholdStats[threshold].truePositives++;
						else
							thresholdStats[threshold].falsePositives++;
					}
				}
				for (set<int>::iterator it=ids->neighborsSet.begin();it!=ids->neighborsSet.end();it++){
					int nodeAddr = *it;
					// if this node was not detected as an attacker
					if (ids->forwardersMap[nodeAddr].getPacketsDroppedRatio() < threshold){
						if (isAttacker[nodeAddr])
							thresholdStats[threshold].falseNegatives++;
						else
							thresholdStats[threshold].trueNegatives++;
					}
				}
			}
			nodeID++;
		} while (node);

		// additional false positive in case nobody detected some of attacking nodes
		for (map<unsigned int, bool>::iterator it = detectedAsAttacker.begin(); it != detectedAsAttacker.end(); it++){
			// attacker, that has not been detected at all
			if (isAttacker[it->first] && !it->second)
				thresholdStats[threshold].falseNegatives++;
			// benign node, that has been reported
			if (!isAttacker[it->first] && it->second)
				thresholdStats[threshold].falsePositives++;
		}
	}

	// Save stats to output file
	if (par("stats").boolValue()) {
		ofstream ofstr (par("idsThresholdStatsFile"));
		if (ofstr.is_open()){
			ofstr.precision(3);
			for (map<double, IDSStats>::iterator it=thresholdStats.begin(); it!=thresholdStats.end(); it++){
				ofstr
					<< it->first << ";"
					<< it->second.falseNegatives << ";"
					<< it->second.falsePositives << ";"
					<< it->second.trueNegatives << ";"
					<< it->second.truePositives
					<< endl;
			}
			ofstr.close();
		}
	}

	// find best threshold
	unsigned int min = INT_MAX;
	double bestThreshold = -1;
	for (map<double, IDSStats>::iterator it=thresholdStats.begin(); it!=thresholdStats.end(); it++){
		unsigned int sum = it->second.falseNegatives + it->second.falsePositives;
		if (sum < min) {
			bestThreshold = it->first;
			min = sum;
		}
	}

	if (bestThreshold>-1){
		recordScalar("idsBestThreshold", bestThreshold);

		recordScalar("idsFalseNegatives", thresholdStats[bestThreshold].falseNegatives);
		recordScalar("idsFalsePositives", thresholdStats[bestThreshold].falsePositives);
		recordScalar("idsTrueNegatives", thresholdStats[bestThreshold].trueNegatives);
		recordScalar("idsTruePositives", thresholdStats[bestThreshold].truePositives);
	}

	// Get overall memory usage
	nodeID = 0;
	double usedMemory = 0;
	do {
		node = network->getSubmodule("node", nodeID);
		ids = node!=NULL?FindModule<IDSSimpleLayer*>::findSubModule(node):NULL;

		if (ids != NULL){
			usedMemory += ids->usedMemory;
		}

		nodeID++;
	} while (node);
	recordScalar("idsUsedMemory", usedMemory, "B");

	// normalized memory usage (via configurable max memory)
	double normMemoryUsage = usedMemory / (nodeID*par("moteMemory").doubleValue());
	recordScalar("normMemoryUsage", normMemoryUsage, "B");

	// Get overall energy stats
	BaseBattery* battery;
	nodeID = 0;
	double consumedNetworkEnergy = 0;
	double nominalNetworkEnergy = 0;
	do {
		if ((node = network->getSubmodule("node", nodeID)) != NULL){

			battery = FindModule<BaseBattery*>::findSubModule(node);
			if (battery) {
				double estimate = battery->estimateResidualAbs();
				double estimateRel = battery->estimateResidualRelative();
				double nominal = estimate / estimateRel;
				nominalNetworkEnergy += nominal;
				consumedNetworkEnergy += nominal - estimate;
				debugEV << "Node " << nodeID << " consumed " << (nominal - estimate) << " mW" << endl;
			}
			nodeID++;
		}
	} while (node);
	debugEV << "Whole network consumed " << consumedNetworkEnergy << " mW" << endl;

	recordScalar("consumedNetworkEnergy", consumedNetworkEnergy, "mW");
	// normalized energy consumption
	double normNetworkEnergy = consumedNetworkEnergy/nominalNetworkEnergy;
	recordScalar("normNetworkEnergy", normNetworkEnergy, "mW");

}

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

#include "SimHelper.h"
#include <iostream>
#include <fstream>
#include <float.h>
#include <FindModule.h>
#include <BaseMobility.h>
#include <BaseNetwLayer.h>
#include <WiseRoute.h>
#include "PolicemenApplLayer.h"
#include "PolicemenBMacLayer.h"

Define_Module(SimHelper);

using namespace std;

void SimHelper::initialize(int stage){
	BaseModule::initialize(stage);
	if (stage==0){
		debug = par("debug").boolValue();
		network = FindModule<>::findNetwork(this);

	} else if (stage==1){
	}
}

void SimHelper::finish(){
	if (debug){
		writeTopology();
//		writeIDSForwardersStats();
//		writeNeighbors();

//		 Compute statistics
//		int nodeID = 0;
//		cModule* node;
//		IDSSimpleLayer* ids;
//		StaticNetwLayer* netw;

		// Stats
	/*	cLongHistogram numNeighbors, destNeighbours, packetsSomebody2Somebody;
		map<unsigned int, bool> isAttacker;
		unsigned int linksWhite2White = 0, linksWhite2Black = 0, linksBlack2Black = 0;
*/
		// Get all attackers
		/*nodeID = 0;
		do {
			node = network->getSubmodule("node", nodeID);
			netw = node!=NULL?FindModule<StaticNetwLayer*>::findSubModule(node):NULL;
			if (netw != NULL)
				isAttacker[nodeID] = netw->pPacketDropping>0;
			nodeID++;
		} while (node);

*/		// For each node
/*		nodeID = 0;
		do {
			node = network->getSubmodule("node", nodeID);
			ids = node!=NULL?FindModule<IDSSimpleLayer*>::findSubModule(node):NULL;

			// Collect data
			if (ids != NULL){
				packetsSomebody2Somebody.collect(ids->numSomebody2Somebody);
				numNeighbors.collect(ids->neighborsSet.size());

				for (set<int>::iterator n=ids->neighborsSet.begin(); n!=ids->neighborsSet.end(); n++){
					int neighAddr = (*n);
					destNeighbours.collect(getNodeDistance(nodeID, neighAddr));

					if (!isAttacker[nodeID] && !isAttacker[neighAddr])
						linksWhite2White++;
					if ((isAttacker[nodeID] && !isAttacker[neighAddr]) || (!isAttacker[nodeID] && isAttacker[neighAddr]))
						linksWhite2Black++;
					if (isAttacker[nodeID] && isAttacker[neighAddr])
						linksBlack2Black++;

				}
			}

			nodeID++;
		} while (node);

		// Record data
		numNeighbors.recordAs("numNeighbors");
		destNeighbours.recordAs("destNeighbors");
		packetsSomebody2Somebody.recordAs("packetsSomebody2Somebody");
		recordScalar("linksWhite2White", linksWhite2White);
		recordScalar("linksWhite2Black", linksWhite2Black);
		recordScalar("linksBlack2Black", linksBlack2Black);*/
	}
}

/**
 * Writes topology stats into topologyStatsFile
 */
void SimHelper::writeTopology(){
	if (par("topologyStatsFile").str().empty()) return;

	ofstream ofstr (par("topologyStatsFile"));
	if (ofstr.is_open()){
		ofstr.precision(3);
		double scale = 7;

		ofstr << "digraph topology {" << endl;

		ofstr << "\tgraph [fontsize = 12, outputorder=\"edgesfirst\", size=\""
				<< getParentModule()->par("playgroundSizeX").doubleValue()/scale
				<<"," << getParentModule()->par("playgroundSizeY").doubleValue()/scale
				<< "\"];" << endl;
		ofstr << "\tnode [color = \"/pastel16/3\", penwidth = 1];" << endl;
		ofstr << "\tedge [fontsize = 10, arrowsize = 0.5];" << endl;

		int nodeID = 0;
		cModule* node;
		BaseMobility* mob;
//		WiseRoute* netw;
//		PolicemenApplLayer* appl;
		PolicemenBMacLayer* mac;
		do {
			node = network->getSubmodule("node", nodeID);
			if (node != NULL){
				mob = FindModule<BaseMobility*>::findSubModule(node);
//				appl = FindModule<PolicemenApplLayer*>::findSubModule(node);
				mac = FindModule<PolicemenBMacLayer*>::findSubModule(node);

				Coord pos1 = mob->getCurrentPosition();

				ofstr << "\t" << nodeID << " [";
				ofstr << "label = \"";
				ofstr << nodeID;
				ofstr << "\"";

				stringstream tmp;
				tmp << ", pos=\"" << pos1.x/scale << "," << pos1.y/scale << "!\"";

//				if (appl->getNodeType() != ATTACKER_NONE)
//					tmp<<", color = \"/pastel16/1\"";
//				else if (node->par("isBaseStation").boolValue())
//					tmp<<", color = \"/pastel16/2\"";

				ofstr << tmp.str();
				ofstr << "]" << endl;

				if (mac != NULL){
					std::list<LAddress::L2Type> ancQueue = mac->GetAncestors();
					std::list<LAddress::L2Type>::iterator it;
					for (it = ancQueue.begin(); it != ancQueue.end(); ++it) {
						int nodeAddr = (*it);

						ofstr << "\t" << nodeAddr << " -> " << nodeID << " [color=lightgrey, arrowhead=empty, penwidth=0.5, label=\"" ;
						//ofstr << getNodeDistance(nodeID, nodeAddr) << "m";
						ofstr << "\"";
						ofstr << "]" << endl;
					}
				}
			}
			nodeID++;
		} while (node);

		ofstr << "}" << endl;
		ofstr.close();
	}
}


/**
 * Writes neighbor stats into resultNeighborsFile
 */
void SimHelper::writeNeighbors(){
	/*if (par("neighbourStatsFile").str().empty()) return;

	ofstream ofstr (par("neighbourStatsFile"));
	if (ofstr.is_open()){
		ofstr.precision(3);

		int nodeID = 0;
		cModule* node;
		IDSSimpleLayer* ids;
		do {
			node = network->getSubmodule("node", nodeID);
			ids = node!=NULL?FindModule<IDSSimpleLayer*>::findSubModule(node):NULL;

			if (ids != NULL){
				for (std::set<int>::iterator it=ids->neighborsSet.begin(); it!=ids->neighborsSet.end(); it++){
					int nodeAddr = (*it);
					ofstr
						<< nodeID << ";"
						<< nodeAddr << ";"
						<< getNodeDistance(nodeID, nodeAddr) << ";"
						<< endl;
				}
			}
			nodeID++;
		} while (node);

		ofstr.close();
	}*/
}

/**
 * Writes IDS stats (selective forwarders) into resultIDSForwardersFile
 */
void SimHelper::writeIDSForwardersStats(){
	/*if (par("idsForwardersStatsFile").str().empty()) return;

	ofstream ofstr (par("idsForwardersStatsFile"));
	if (ofstr.is_open()){
		ofstr.precision(3);

		int nodeID = 0;
		cModule* node;
		IDSSimpleLayer* ids;
		do {
			node = network->getSubmodule("node", nodeID);
			ids = node!=NULL?FindModule<IDSSimpleLayer*>::findSubModule(node):NULL;

			if (ids != NULL){
				for (IDSMap::iterator it=ids->forwardersMap.begin();it!=ids->forwardersMap.end();it++){
					IDSEntry* entry = &(it->second);
					const int nodeAddr = it->first;

					ofstr
						<< nodeID << ";"
						<< nodeAddr << ";"
						<< entry->packetsReceived << ";"
						<< entry->packetsForwarded << ";"
						<< getNodeDistance(nodeID, nodeAddr) << ";"
						<< entry->getPacketsDroppedRatio() << ";"
						<< endl;
				}
			}
			nodeID++;
		} while (node);

		ofstr.close();
	}*/
}

void SimHelper::initMobility(){
/*	const char *mobilityFile = par("mobilityFile");
	unsigned int countLoaded = 0;

	cModule* node;
	StaticMobility* mobility;

	ifstream ifstr (mobilityFile);
	if (ifstr.is_open()){
		string line;
		int id;
		double x,y,z;

		while (ifstr.good()){
			ifstr >> line;

			unsigned int tmp = line.find(";", 0);
			if (tmp==string::npos) continue;
			id = atoi(line.substr(0,tmp).c_str());

			line = line.substr(tmp+1,line.length());
			if ((tmp = line.find(";", 0))==string::npos) continue;
			x = atof(line.substr(0,tmp).c_str());

			line = line.substr(tmp+1,line.length());
			if ((tmp = line.find(";", 0))==string::npos) continue;
			y = atof(line.substr(0,tmp).c_str());

			line = line.substr(tmp+1,line.length());
			z = atof(line.c_str());

			node = getParentModule()->getSubmodule("node", id);
			if (!node) continue;

			mobility = FindModule<StaticMobility*>::findSubModule(node);
			if (!mobility) continue;

			mobility->setPosition(Coord(x, y, z));
			//nodePositions[id] = Coord(x,y,z);	 alternative
			countLoaded++;
		}
		ifstr.close();
	}
	debugEV << "Loaded " << countLoaded << " items from mobilityFile " << mobilityFile << endl;*/
}


void SimHelper::initRouting(){
	/*const char *routingFile = par("routingFile");
	unsigned int countLoaded = 0;

	int nextHopAddr, sinkAddr;

	ifstream ifstr (routingFile);
	if (ifstr.is_open()){
		string line;

		while (ifstr.good()){
			ifstr >> line;

			unsigned int tmp = line.find(";", 0);
			if (tmp==string::npos) continue;

			int id = atoi(line.substr(0,tmp).c_str());
			line = line.substr(tmp+1,line.length());

			tmp = line.find(";", 0);
			if (tmp==string::npos) continue;

			nextHopAddr = atoi(line.substr(0,tmp).c_str());
			line = line.substr(tmp+1,line.length());
			sinkAddr = atoi(line.c_str());

			cModule* node = getParentModule()->getSubmodule("node", id);
			if (!node) continue;

			StaticNetwLayer* netw = FindModule<StaticNetwLayer*>::findSubModule(node);
			if (!netw) continue;

			if (netw->par("readFromFile").boolValue())
				netw->setNextHopAddr(nextHopAddr);

			countLoaded++;
		}
		ifstr.close();
	}
	debugEV << "Loaded " << countLoaded << " items from routeFile " << routingFile << endl;*/
}

bool SimHelper::hasNodePos(int nodeID){
	return nodePositions.count(nodeID)>0;
}
const Coord SimHelper::getNodePos(int nodeID){
	if (hasNodePos(nodeID))
		return nodePositions[nodeID];
	else
		return NULL;
}

double SimHelper::getNodeDistance(int nodeA, int nodeB){
	if (hasNodePos(nodeA) && hasNodePos(nodeB))
		return getNodePos(nodeA).distance(getNodePos(nodeB));
	else
		return DBL_MAX;
}

void SimHelper::receiveSignal(cComponent *source, simsignal_t signalID, cObject *obj){
	/*BaseModule::receiveSignal(source, signalID, obj);

	if (signalID == mobilityStateChangedSignal){
		BaseMobility* const mobility = check_and_cast<BaseMobility*>(obj);
		cModule* node = FindModule<>::findHost(mobility);
		Coord pos = mobility->getCurrentPosition();
		nodePositions[node->getIndex()] = pos;
		debugEV << "Node " << node->getIndex() << " changed position to " << pos << endl;
	}*/
}

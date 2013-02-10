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

#include <omnetpp.h>
#include <sstream>
#include <FindModule.h>
#include "IDSSimpleLayer.h"
#include "StaticNetwLayer.h"
#include "StaticNetwPkt_m.h"
#include "MacPkt_m.h"

Define_Module(IDSSimpleLayer);

using namespace std;

/**
 * Initialize module
 */
void IDSSimpleLayer::initialize(int stage){
	IDSLayer::initialize(stage);
	if (stage==0){
		net = FindModule<StaticNetwLayer*>::findSubModule(getNode());
		helper = FindModule<SimHelper*>::findGlobalModule();
		maxDistance = par("maxDistance").doubleValue();
		maxMonitoredNodes = par("maxMonitoredNodes").longValue();
		fwdBufferSize = par("fwdBufferSize").longValue();
		fwdMinPacketsReceived = par("fwdMinPacketsReceived").longValue();
		fwdPacketTimeout = par("fwdPacketTimeout").doubleValue();
		fwdDetectionThreshold = par("fwdDetectionThreshold").doubleValue();

		usedMemory = maxMonitoredNodes * par("memIDSEntry").doubleValue() + fwdBufferSize * par("memBufferEntry").doubleValue();
		maxNeighbor = -1;
		numInterceptedPackets = 0;
		numSomebody2Me = numSomebody2Somebody = numMe2Somebody = 0;
		evaluated = false;
	}
}

/**
 * Handle messages from upper (network) layer
 */
void IDSSimpleLayer::handleUpperMsg(cMessage *msg){
	MacPkt* macPkt = static_cast<MacPkt *> (msg);

	StaticNetwPkt* netwPkt = dynamic_cast<StaticNetwPkt *> (macPkt->getEncapsulatedPacket());
	if (netwPkt)
		analyseNetwPkt(netwPkt);

	IDSLayer::handleUpperMsg(msg);
}
/**
 * Handle messages from lower (physical) layer
 */
void IDSSimpleLayer::handleLowerMsg(cMessage *msg){
	MacPkt* macPkt = static_cast<MacPkt *> (msg);

	StaticNetwPkt* netwPkt = dynamic_cast<StaticNetwPkt *> (macPkt->getEncapsulatedPacket());
	if (netwPkt)
		analyseNetwPkt(netwPkt);

	IDSLayer::handleLowerMsg(msg);
}

/**
 * Finalize module
 */
void IDSSimpleLayer::finish(){
	BaseLayer::finish();
	//LOCAL EVALUATION CURRENTLY TURNED ON!
	doEvaluation();

	if (!par("stats").boolValue()) return;

	// compute various statistics
	cOutVector neighborsVector("neighbors");
	for (std::set<int>::iterator it=neighborsSet.begin(); it!=neighborsSet.end(); it++)
		neighborsVector.record((*it));

	cOutVector forwardersVector("forwardersMap");
	for (IDSMap::iterator it=forwardersMap.begin();it!=forwardersMap.end();it++)
		forwardersVector.record(it->first);

	recordScalar("data_packets_intercepted", numInterceptedPackets);
	recordScalar("data_packets_me_to_somebody", numMe2Somebody);
	recordScalar("data_packets_somebody_to_me", numSomebody2Me);
	recordScalar("data_packets_somebody_to_somebody", numSomebody2Somebody);

	/*recordScalar("neighbors", neighborsSet.size());
	recordScalar("forwarders_falseNegatives", forwardersStats.falseNegatives);
	recordScalar("forwarders_falsePositives", forwardersStats.falsePositives);
	recordScalar("forwarders_trueNegatives", forwardersStats.trueNegatives);
	recordScalar("forwarders_truePositives", forwardersStats.truePositives);
	*/
}

/**
 * Analyse received network packet
 */
void IDSSimpleLayer::analyseNetwPkt(StaticNetwPkt* netwPkt){
	// packet is OK, analyse it
	if (netwPkt != NULL){

		// compute stats
		numInterceptedPackets++;
		if (netwPkt->getSrcAddr()==net->getNetwAddr()){
			numMe2Somebody++;
		} else {
			if (netwPkt->getDestAddr()==net->getNetwAddr()) numSomebody2Me++;
			else numSomebody2Somebody++;
		}

		// write info about received packet
		EV << "IDS on "<< net->getNetwAddr() << " received packet:"
		<< " src=" << netwPkt->getSrcAddr() << " (" << helper->getNodeDistance(net->getNetwAddr(), netwPkt->getSrcAddr()) << " m)"
		<< " dest=" << netwPkt->getDestAddr() << " (" << helper->getNodeDistance(net->getNetwAddr(), netwPkt->getDestAddr()) << " m)"
		<< " initialSrc=" << netwPkt->getInitialSrcAddr()
		<< " finalDest=" << netwPkt->getFinalDestAddr()
		<< " seqNum=" << netwPkt->getSeqNum()
		<< " nbHops=" << netwPkt->getNbHops()
		<< " creationTime=" << netwPkt->getCreationTime().str()
		<< endl;

		// add to neighborsSet
		if (netwPkt->getSrcAddr()!=net->getNetwAddr() && neighborsSet.count(netwPkt->getSrcAddr())==0){
			if (maxNeighbor==-1 || helper->getNodeDistance(net->getNetwAddr(), netwPkt->getSrcAddr()) > helper->getNodeDistance(net->getNetwAddr(), maxNeighbor))
				maxNeighbor = netwPkt->getSrcAddr();
			neighborsSet.insert(netwPkt->getSrcAddr());
		}

		double dist2dest = helper->getNodeDistance(net->getNetwAddr(), netwPkt->getDestAddr());

		// packet is being forwarded and we are monitoring the source node
		if (netwPkt->getSrcAddr() != netwPkt->getInitialSrcAddr() &&
				netwPkt->getSrcAddr() != net->getNetwAddr() &&
				helper->getNodeDistance(net->getNetwAddr(), netwPkt->getSrcAddr()) <= maxDistance){

			if (forwardersMap.count(netwPkt->getSrcAddr())>0){
				debugEV<< "Node " << netwPkt->getSrcAddr() << " forwarded this packet " << endl;

				for(FwdBuffer::iterator entry=fwdBuffer.begin(); entry!=fwdBuffer.end(); entry++){
					if (entry->destAddr == netwPkt->getFinalDestAddr() &&
							entry->srcAddr == netwPkt->getInitialSrcAddr() &&
							entry->creationTime == netwPkt->getCreationTime().raw() &&
							entry->nodeAddr == netwPkt->getSrcAddr()){

						forwardersMap[netwPkt->getSrcAddr()].packetsForwarded++;
						debugEV<< "Packet removed from fwdBuffer" << endl;

						fwdBuffer.erase(entry);
						break;
					}
				}
			}
		}

		// packet should be forwarded and we are monitoring the destination node (is close enough and our neighbor or routing tree parent)
		if (netwPkt->getDestAddr() != netwPkt->getFinalDestAddr() &&
				netwPkt->getDestAddr() != net->getNetwAddr() &&
				dist2dest <= maxDistance &&
				(neighborsSet.count(netwPkt->getDestAddr()) > 0 || net->getNextHopAddr() == netwPkt->getDestAddr())){

			bool monitor = true;

			// we need to throw something out from forwardersMap
			if (forwardersMap.count(netwPkt->getDestAddr())==0 && forwardersMap.size()>=maxMonitoredNodes){
				// find node with maximum distance so far
				double foundDist = 0;
				int foundNode = -1;

				for(IDSMap::iterator entry=forwardersMap.begin(); entry!=forwardersMap.end(); entry++){
					double dist = helper->getNodeDistance(net->getNetwAddr(), entry->first);
					// possible candidate only if distant enough and not my parent in routing tree
					if (dist > foundDist && net->getNextHopAddr() != entry->first){
						foundDist = dist;
						foundNode = entry->first;
					}
				}

				// if there is worse entry in the map, remove it and insert new one
				if (foundDist > dist2dest || net->getNextHopAddr() == netwPkt->getDestAddr()){
					debugEV<< "Removing node " << foundNode << " from forwardersMap" << endl;
					forwardersMap.erase(foundNode);

					// remove all packets from fwdBuffer
					for(FwdBuffer::iterator entry=fwdBuffer.begin(); entry!=fwdBuffer.end(); ){
						if (entry->nodeAddr == netwPkt->getDestAddr())
							entry = fwdBuffer.erase(entry);
						else
							entry++;
					}
				}

				// Is it possible to monitor given node?
				if (forwardersMap.count(netwPkt->getDestAddr())==0 && forwardersMap.size()>=maxMonitoredNodes)
				    monitor = false;

			}

			// if the packet is being monitored
			if (monitor){
				// update buffer and create one empty slot
				updateFwdBuffer(true);

				if (fwdBuffer.size()<fwdBufferSize){
					FwdEntry fwdEntry;
					fwdEntry.timeout = simTime() + SimTime(fwdPacketTimeout);
					fwdEntry.srcAddr = netwPkt->getInitialSrcAddr();
					fwdEntry.destAddr = netwPkt->getFinalDestAddr();
					fwdEntry.nodeAddr = netwPkt->getDestAddr();
					fwdEntry.creationTime = netwPkt->getCreationTime().raw();
					fwdBuffer.push_back(fwdEntry);

					// increment PR
					forwardersMap[netwPkt->getDestAddr()].packetsReceived++;

					// log
					debugEV<< "Node " << netwPkt->getDestAddr() << " should forward packet " << endl;
				}
			}
		}
	} else {
		debugEV << "Node " << net->getNetwAddr() << " received unknown packet" << endl;
	}
}


/**
 * Updates buffer of packets, that need to be forwarded
 */
void IDSSimpleLayer::updateFwdBuffer(bool needOneSlot){
	// check timeouts and throw away old packets
	for(FwdBuffer::iterator entry=fwdBuffer.begin(); entry!=fwdBuffer.end(); ){
		if (simTime() >= entry->timeout){
			debugEV << "Packet is old, deleting (" << entry->srcAddr << "->" << entry->destAddr << ")" << endl;
			debugEV << "SimTime=" << simTime() << ", timeout=" << entry->timeout << endl;
			entry = fwdBuffer.erase(entry);
		} else {
			entry++;
		}
	}
	// we need one empty slot and buffer is full => delete oldest packet
	if (needOneSlot && fwdBuffer.size()>0 && fwdBuffer.size()>=fwdBufferSize){
		FwdEntry* entry = &fwdBuffer.front();
		debugEV << "Buffer is full, deleting packet (" << entry->srcAddr << "->" << entry->destAddr << ")" << endl;
		fwdBuffer.pop_front();
	}
}
/**
 * Perform IDS evaluation and compute stats
 */
void IDSSimpleLayer::doEvaluation(){
	if (evaluated) return;

	forwardersStats.reset();

	cModule* network = FindModule<>::findNetwork(this);
	cModule* node;
	StaticNetwLayer* netw;

	// check forwarders
	for (IDSMap::iterator i=forwardersMap.begin();i!=forwardersMap.end();i++){
		IDSEntry* entry = &(i->second);
		const int nodeAddr = i->first;
		stringstream ss1;
		ss1 << "neighbour"<<nodeAddr<< "PacketsReceived";
	        recordScalar(ss1.str().c_str(),entry->packetsReceived);
		ss1.str("");
		ss1 << "neighbour"<<nodeAddr<< "PacketsForwarded";
	        recordScalar(ss1.str().c_str(),entry->packetsForwarded);
		ss1.str("");
		// get node
		node = network->getSubmodule("node", nodeAddr);
		netw = FindModule<StaticNetwLayer*>::findSubModule(node);
		if (!netw) continue;
		ss1 << "neighbour"<<nodeAddr<< "IntentionalPacketDropping";
	        recordScalar(ss1.str().c_str(),netw->pPacketDropping);
	}

	//evaluated = true;
}

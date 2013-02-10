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

#include "StaticNetwLayer.h"
#include <omnetpp.h>

#include <ApplPkt_m.h>
#include <NetwPkt_m.h>
#include <NetwControlInfo.h>
#include <ArpInterface.h>

#include "StaticNetwPkt_m.h"

Define_Module(StaticNetwLayer);

StaticNetwLayer::StaticNetwLayer() {
	// TODO Auto-generated constructor stub

}

StaticNetwLayer::~StaticNetwLayer() {
	// TODO Auto-generated destructor stub
}

void StaticNetwLayer::initialize(int stage){
	BaseNetwLayer::initialize(stage);

	if(stage == 0){
		setNextHopAddr(par("nextHopAddr").doubleValue());
		pPacketDropping = par("pPacketDropping").doubleValue();
		fwdPacketWait = par("fwdPacketWait").doubleValue();
		nbPacketsSent = nbPacketsForwarded = nbPacketsReceived = nbPacketsDropped = 0;
	} else if(stage == 1) {

	}
}
void StaticNetwLayer::finish(){
	recordScalar("nbPacketsForwarded", nbPacketsForwarded);
	recordScalar("nbPacketsReceived", nbPacketsReceived);
	recordScalar("nbPacketsSent", nbPacketsSent);
	recordScalar("nbPacketsDropped", nbPacketsDropped);
}

void StaticNetwLayer::setNextHopAddr(int addr){
	nextHopAddr = addr;
}

int StaticNetwLayer::getNextHopAddr(){
	return nextHopAddr;
}

void StaticNetwLayer::handleUpperMsg(cMessage* msg){
	BaseNetwLayer::handleUpperMsg(msg);
	nbPacketsSent++;
}

LAddress::L3Type StaticNetwLayer::getNetwAddr(){
	return myNetwAddr;
}

void StaticNetwLayer::handleLowerMsg(cMessage* msg){

	StaticNetwPkt* pkt = check_and_cast<StaticNetwPkt*>(msg);
	debugEV << "Node " << myNetwAddr << " received packet " << pkt->getSrcAddr() << "->" << pkt->getDestAddr() << " (" << pkt->getInitialSrcAddr() << "->" << pkt->getFinalDestAddr() << ", " << pkt->getNbHops() << " hops)" << endl;
	nbPacketsReceived++;

	// Packet should be forwarded
	if (pkt->getFinalDestAddr() != pkt->getDestAddr()) {

		// Selective forwarding attack
		if (pPacketDropping>=uniform(0,1)) {
			EV << "[ATTACK] Node "<<myNetwAddr<<" is dropping packet " << pkt->getSrcAddr() <<" -> "<<pkt->getDestAddr()<<endl;
			nbPacketsDropped++;
			delete msg;
			msg = NULL;
			return;
		}

		// Forward packet
		LAddress::L3Type pktNextHopAddr = LAddress::isL3Broadcast(pkt->getFinalDestAddr()) ? LAddress::L3BROADCAST : (nextHopAddr == -1 ? pkt->getFinalDestAddr() : nextHopAddr);
		LAddress::L2Type pktNextHopMacAddr = LAddress::isL3Broadcast(pktNextHopAddr) ? LAddress::L2BROADCAST : arp->getMacAddr(pktNextHopAddr);

		pkt->setSrcAddr(myNetwAddr);
		pkt->setDestAddr(pktNextHopAddr);
		pkt->setNbHops(pkt->getNbHops()+1);

		EV << "Node " << myNetwAddr << " forwards packet " << pkt->getInitialSrcAddr() << "->" << pkt->getFinalDestAddr() << " via " <<  pkt->getDestAddr() << endl;

		cObject* cInfo = msg->removeControlInfo();
		if (cInfo) delete cInfo;
		setDownControlInfo(pkt, pktNextHopMacAddr);

		recordPacket(PassedMessage::OUTGOING,PassedMessage::LOWER_DATA,msg);
		sendDelayed(msg, uniform(0, fwdPacketWait), lowerLayerOut);

		nbPacketsForwarded++;

	} else {
		BaseNetwLayer::handleLowerMsg(msg);
	}
}

/**
 * Encapsulate message
 */
NetwPkt* StaticNetwLayer::encapsMsg(cPacket *appPkt) {
	LAddress::L3Type pktFinalDestAddr;
	LAddress::L3Type pktNextHopAddr;
	LAddress::L2Type pktNextHopMacAddr;

    StaticNetwPkt *pkt = new StaticNetwPkt(appPkt->getName(), appPkt->getKind());
    pkt->setBitLength(headerLength);

    cObject* cInfo = appPkt->removeControlInfo();

    if(cInfo == NULL){
    	EV << "warning: Application layer did not specify a destination L3 address\n"
    			<< "\tusing broadcast address instead\n";
    	pktFinalDestAddr = LAddress::L3BROADCAST;
    } else {
    	coreEV <<"CInfo removed, netw addr="<< NetwControlInfo::getAddressFromControlInfo( cInfo ) << std::endl;
    	pktFinalDestAddr = NetwControlInfo::getAddressFromControlInfo( cInfo );
        delete cInfo;
    }

    pktNextHopAddr = LAddress::isL3Broadcast(pktFinalDestAddr) ? LAddress::L3BROADCAST : (nextHopAddr == -1 ? pktFinalDestAddr : nextHopAddr);
    pktNextHopMacAddr = LAddress::isL3Broadcast(pktNextHopAddr) ? LAddress::L2BROADCAST : arp->getMacAddr(pktNextHopAddr);

	debugEV << "Sending packet to " << pktFinalDestAddr << " via " << pktNextHopAddr << " (MAC " << pktNextHopMacAddr << ")" << endl;

    pkt->setFinalDestAddr(pktFinalDestAddr);
    pkt->setInitialSrcAddr(myNetwAddr);
    pkt->setSrcAddr(myNetwAddr);
    pkt->setDestAddr(pktNextHopAddr);
    pkt->setNbHops(0);

    setDownControlInfo(pkt, pktNextHopMacAddr);

    //encapsulate the application packet
    pkt->encapsulate(appPkt);

    return pkt;
}

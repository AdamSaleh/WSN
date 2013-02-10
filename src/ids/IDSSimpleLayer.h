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

#ifndef IDSSIMPLELAYER_H_
#define IDSSIMPLELAYER_H_

#include <omnetpp.h>
#include <map>
#include <vector>
#include <deque>
#include <set>
#include <BMacLayer.h>
#include <MacPkt_m.h>
#include <ApplPkt_m.h>

#include "IDSLayer.h"
#include "StaticNetwLayer.h"
#include "StaticNetwPkt_m.h"
#include "SimHelper.h"


/**
 * Entry in IDS table
 */
struct IDSEntry {
	unsigned int packetsReceived, packetsForwarded;

	IDSEntry(){
		packetsReceived = packetsForwarded = 0;
	}
	double getPacketsDroppedRatio(){
		return packetsReceived>0?(packetsReceived-packetsForwarded)/(double)packetsReceived:0;
	}
};
typedef std::map<int, IDSEntry> IDSMap;

/**
 * Entry in forwarders table
 */
struct FwdEntry {
	int srcAddr;
	int destAddr;
	int nodeAddr;
	int64 creationTime;

	simtime_t timeout;

	FwdEntry(){
		srcAddr = destAddr = nodeAddr = creationTime = -1;
	}
};
typedef std::pair<int, int64> FwdMapIndex;
typedef std::map<FwdMapIndex, FwdEntry> FwdMap;
typedef std::deque<FwdEntry> FwdBuffer;

/**
 * IDS statistics
 */
typedef struct _IDSStats {
	unsigned long falsePositives;
	unsigned long falseNegatives;
	unsigned long truePositives;
	unsigned long trueNegatives;

	_IDSStats(){
		reset();
	}
	void reset(){
		falsePositives = falseNegatives = truePositives = trueNegatives = 0;
	}
} IDSStats;


class IDSSimpleLayer : public IDSLayer {

protected:
	bool evaluated;
	double maxDistance;
	unsigned int maxMonitoredNodes;
	double monitoringTime;

	SimHelper* helper;
	StaticNetwLayer* net;

	FwdBuffer fwdBuffer;

	virtual void handleUpperMsg(cMessage *msg);
	virtual void handleLowerMsg(cMessage *msg);

	void analyseNetwPkt(StaticNetwPkt* netwPkt);
	void updateFwdBuffer(bool needOneSlot=false);

public:
	virtual void finish();
	virtual void initialize(int stage);
	void doEvaluation();

	IDSStats forwardersStats;
	IDSMap forwardersMap;
	std::set<int> neighborsSet;
	double maxNeighbor;
	unsigned long int usedMemory;
	unsigned int numInterceptedPackets;
	unsigned int numSomebody2Me, numSomebody2Somebody, numMe2Somebody;

	unsigned int fwdBufferSize, fwdMinPacketsReceived;
	double fwdPacketTimeout, fwdDetectionThreshold;
};


#endif /* IDSSIMPLELAYER_H_ */

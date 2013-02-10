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

#include "SensorApplLayerEx.h"

Define_Module(SensorApplLayerEx);

void SensorApplLayerEx::initializeDistribution(const char* traffic) {
	if (!strcmp(traffic, "slots")) {
		trafficType = SLOTS;
	} else {
		SensorApplLayer::initializeDistribution(traffic);
	}
}

void SensorApplLayerEx::scheduleNextPacket() {
	if (trafficType != SLOTS){
		SensorApplLayer::scheduleNextPacket();
		return;
	}
	if (nbPackets > sentPackets && trafficType != 0) { // We must generate packets
		simtime_t nextTime = initializationTime + sentPackets*trafficParam + uniform(0, trafficParam);
		debugEV<< "Periodic traffic, nextTime=" << nextTime << endl;
		scheduleAt(nextTime, delayTimer);
	} else {
		debugEV << "All packets sent.\n";
	}
}

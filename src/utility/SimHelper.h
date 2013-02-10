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

#ifndef SIMHELPER_H_
#define SIMHELPER_H_

#include <BaseModule.h>
#include <Coord.h>

class SimHelper : public BaseModule {
protected:
	cModule* network;

	std::map<int, Coord> nodePositions;
	/** @brief A signal used to subscribe to mobility state changes. */
	const static simsignalwrap_t mobilityStateChangedSignal;

	void initMobility();
	void initRouting();

	void writeTopology();
	void writeNeighbors();
	void writeIDSForwardersStats();
public:
	virtual void initialize(int stage);
	virtual void finish();
    virtual void receiveSignal(cComponent *source, simsignal_t signalID, cObject *obj);
    bool hasNodePos(int nodeID);
	const Coord getNodePos(int nodeID);
	double getNodeDistance(int nodeA, int nodeB);
};

#endif /* SIMHELPER_H_ */

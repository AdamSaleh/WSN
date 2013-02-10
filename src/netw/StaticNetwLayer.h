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

#ifndef STATICNETWLAYER_H_
#define STATICNETWLAYER_H_

#include <BaseNetwLayer.h>
#include <NetwPkt_m.h>

class StaticNetwLayer: public BaseNetwLayer {
protected:
	int nextHopAddr;
	int nbPacketsSent, nbPacketsForwarded, nbPacketsReceived, nbPacketsDropped;
	double fwdPacketWait;

public:
	double pPacketDropping;

	StaticNetwLayer();
	virtual ~StaticNetwLayer();

	void setNextHopAddr(int addr);
	int getNextHopAddr();

	virtual void initialize(int stage);
	virtual void finish();
	LAddress::L3Type getNetwAddr();

	virtual NetwPkt* encapsMsg(cPacket *appPkt);
    virtual void handleLowerMsg(cMessage* msg);
    virtual void handleUpperMsg(cMessage* msg);
};

#endif /* STATICNETWLAYER_H_ */

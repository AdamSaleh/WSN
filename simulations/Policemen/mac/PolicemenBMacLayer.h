#ifndef POLICEMENBMACLAYER_H_
#define POLICEMENBMACLAYER_H_

//#include "DataPkt_m.h"
#include <BMacLayer.h>

class PolicemenBMacLayer: public BMacLayer {
public:
    typedef std::list<LAddress::L2Type> AncestorQueue;

	PolicemenBMacLayer()
		: BMacLayer()
		, ancQueue()
	{}
	virtual ~PolicemenBMacLayer();

	virtual bool alreadyInQueue(cPacket*);

	virtual bool queueIsEmpty();

	/** @brief Initialization of the module and some variables*/
	virtual void initialize(int);

	/** @brief Handle self messages such as timers */
	virtual void handleSelfMsg(cMessage*);

	virtual std::list<LAddress::L2Type> GetAncestors();
protected:
    AncestorQueue ancQueue;
};

#endif /* POLICEMENBMACLAYER_H_ */

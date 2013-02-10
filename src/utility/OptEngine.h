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

#ifndef OPTENGINE_H_
#define OPTENGINE_H_

#include <BaseModule.h>
#include <cmessage.h>
#include <map>

class OptEngine : public BaseModule  {
protected:
	enum OPTENGINE_MSG_TYPES {
		FRACTION_DONE_TIMER,
	};
	cMessage* fractionDoneTimer;	// timer for publishing simulation progress outside
	cModule* network;
	double simtimelimit;
public:
	virtual void initialize(int stage);
	virtual void finish();
	virtual ~OptEngine();
	virtual void handleMessage(cMessage *msg);
};

#endif /* OPTENGINE_H_ */

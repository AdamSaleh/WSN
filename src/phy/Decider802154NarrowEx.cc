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

#include "Decider802154NarrowEx.h"
#include <BaseDecider.h>
#include <AirFrame_m.h>

simtime_t Decider802154NarrowEx::processNewSignal(AirFrame* frame) {
	Signal& s = frame->getSignal();
	simtime_t receivingStart = MappingUtils::post(s.getReceptionStart());
	double recvPower = s.getReceivingPower()->getValue(Argument(receivingStart));

	// check whether signal is strong enough to receive
	if ( recvPower < sensitivity )
	{
		deciderEV << "Signal is to weak (" << recvPower << " < " << sensitivity
				<< ") -> do not receive." << endl;
		// Signal too weak, we can't receive it, tell PhyLayer that we don't want it again
		return notAgain;
	}

	return Decider802154Narrow::processNewSignal(frame);
}


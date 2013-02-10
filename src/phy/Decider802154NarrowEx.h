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

#ifndef DECIDER802154NARROWEX_H_
#define DECIDER802154NARROWEX_H_

#include <Decider802154Narrow.h>

class Decider802154NarrowEx : public Decider802154Narrow {
protected:
	double sensitivity;
	virtual simtime_t processNewSignal(AirFrame* frame);

public:
	Decider802154NarrowEx(DeciderToPhyInterface* phy,
						double sensitivity,
						int myIndex,
						bool debug,
						int sfdLength,
						double BER_LOWER_BOUND,
						const std::string& modulation, int phyHeaderLength, bool recordStats):
		Decider802154Narrow(phy, myIndex, debug, sfdLength, BER_LOWER_BOUND, modulation, phyHeaderLength, recordStats),
		sensitivity(sensitivity)
	{
	}
};

#endif /* DECIDER802154NARROWEX_H_ */

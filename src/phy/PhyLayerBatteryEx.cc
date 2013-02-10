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

#include "PhyLayerBatteryEx.h"
#include <omnetpp.h>
#include <PhyLayerBattery.h>
#include <Decider.h>

#include "Decider802154NarrowEx.h"

Define_Module(PhyLayerBatteryEx);

Decider* PhyLayerBatteryEx::getDeciderFromName(std::string name, ParameterMap& params){
	if(name == "Decider802154NarrowEx") {
		return initializeDecider802154NarrowEx(params);
	}

	return PhyLayerBattery::getDeciderFromName(name, params);
}

Decider* PhyLayerBatteryEx::initializeDecider802154NarrowEx(ParameterMap& params){
	int sfdLength = params["sfdLength"];
	double berLowerBound = params["berLowerBound"];
	std::string modulation = params["modulation"].stringValue();
	return new Decider802154NarrowEx(this, sensitivity, findHost()->getIndex(), coreDebug, sfdLength, berLowerBound, modulation, headerLength, recordStats);
}

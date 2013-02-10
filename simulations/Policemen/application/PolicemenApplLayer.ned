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

package policemen.application;

import org.mixim.base.modules.IBaseApplLayer;

simple PolicemenApplLayer like IBaseApplLayer
{
    parameters:
        @class(PolicemenApplLayer);
        bool debug = default(false); // debug switch
        bool stats = default(true);   // stats generation switch
        bool trace = default(false);  // activates detailed logging (per source latencies and vector logging). stats must be true.
        bool broadcastPackets = default(false); // send packets in broadcast mode
        double nbPackets = default(0);
        int destAddr = default(0);
        string trafficType = default("periodic");  	// Can be one of: periodic, uniform or exponential
        double trafficParam @unit(s) = default(1 s);			// the mean time between two packets
        double initializationTime @unit(s) = default(1 min); // minimum time before generation of the first packet
		int headerLength @unit(byte) = default(2 byte);
        bool notAffectedByHostState = default(true);
        double movementDetectedWaitTime @unit(s) = default(0.5 s);
        string nodeType @enum("normal", "attacker","policemen") = default("normal");
        
    gates:
    	input lowerLayerIn; // from network layer
        input lowerControlIn;
        output lowerLayerOut; // to network layer
        output lowerControlOut;
}
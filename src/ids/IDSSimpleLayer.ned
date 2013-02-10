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

package wsn.ids;

//
// Simple IDS for testing purposes
//
simple IDSSimpleLayer extends IDSLayer {
    
    parameters:
        // P1: Max.  number of monitored nodes
        int maxMonitoredNodes = default(20);
        // P2: Size of packet buffer 
        int fwdBufferSize = default(100);
		// P3: Minimum number packets a node has to receive to be included in evaluation
        int fwdMinPacketsReceived = default(0);        
		// P4: Threshold for IDS evaluation of selective forwarders
        double fwdDetectionThreshold = default(0.5);
        
        // memory used for one IDS entry (4B packets received + 4B packets forwarded)        
        double memIDSEntry @unit(B) = default(8B);
        // memory used for one entry in fwdBuffer (4B src address + 4B dest address + 4B middle node address + 4B unique id)
        double memBufferEntry @unit(B) = default(16B);
        
        // Max. monitoring distance
        double maxDistance = default(999999);
        // Timeout for forwarded packets
        double fwdPacketTimeout @unit(s) = default(999999s);
                        
    	@class(IDSSimpleLayer);
}

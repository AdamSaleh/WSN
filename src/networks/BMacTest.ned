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

package wsn.networks;

import org.mixim.modules.node.HostBMAC;
import org.mixim.base.modules.BaseNetwork;
import wsn.utility.SimHelper;
import wsn.utility.OptEngine;
import wsn.node.DefaultNode;

network BMacTest extends BaseNetwork
{
    parameters:
        int numNodes; // total number of hosts in the network
		
    submodules:
        simHelper: SimHelper {
            
        }
        optEngine: OptEngine {
            
        }
        node[numNodes]: DefaultNode {
            mobility.constraintAreaMaxX = playgroundSizeX;
            mobility.constraintAreaMaxY = playgroundSizeY;
            mobility.constraintAreaMaxZ = playgroundSizeZ;
        }
    connections allowunconnected:
    // all connections and gates are to be generated dynamically
}

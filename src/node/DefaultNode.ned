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

package wsn.node;

import org.mixim.modules.netw.ArpHost;
import org.mixim.modules.power.battery.SimpleBattery;
import org.mixim.modules.power.battery.BatteryStats;
import org.mixim.modules.node.HostBMAC;
import org.mixim.modules.node.WirelessNodeBattery;
import wsn.nic.WirelessNicIDSBattery;

module DefaultNode extends WirelessNodeBattery
{
    parameters:
        arpType = default("org.mixim.modules.netw.ArpHost");
        nicType = default("wsn.nic.WirelessNicIDSBattery");

        //applicationType = default("SensorApplLayer");
        //mobilityType = default("StaticMobility");        
        //arpType = default("org.mixim.modules.netw.ArpHost");
        //nicType = default("org.mixim.modules.nic.NicBMAC");
        //transportType = default("Aggregation");
        //nicType = default("NicCC2420BMac");
        //arpType = default("org.mixim.modules.netw.ArpHost");
        //networkType = default("StaticNetwLayer");

        battery.nominal = default(4244mAh);
        battery.capacity = default(battery.nominal);
        battery.voltage = default(3.3V);
        battery.resolution = default(1s);
        battery.publishDelta = default(1);
        battery.publishTime = default(0);
        battery.numDevices = default(1);

        @display("is=vs;b=0,0;i2=device/palm;i=device/palm");
    submodules:
}

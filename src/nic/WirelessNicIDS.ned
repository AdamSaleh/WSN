package wsn.nic;

import org.mixim.base.phyLayer.IWirelessPhy;
import org.mixim.base.modules.IWirelessMac;
import org.mixim.modules.nic.IWirelessNicUpperCtrl;

import wsn.ids.IWirelessIDS;

//
// Basic wireless nic definition
//
module WirelessNicIDS like IWirelessNicUpperCtrl
{
    parameters:
        string connectionManagerName = default("");   //name of the ConnectionManager module
        string phyType = default("org.mixim.modules.phy.PhyLayer");
        string macType = default("org.mixim.modules.mac.CSMAMacLayer");
        string idsType = default("wsn.ids.IDSLayer");

    gates:
        input upperLayerIn; // to upper layers
        output upperLayerOut; // from upper layers
        output upperControlOut; // control information 
        input upperControlIn; // control information 
        input radioIn; // radioIn gate for sendDirect

    submodules:
        mac: <macType> like IWirelessMac {
            @display("p=52,51;i=block/layer");
        }

        ids: <idsType> like IWirelessIDS {
            @display("p=52,127;i=block/cogwheel");
        }

        phy: <phyType> like IWirelessPhy {
            @display("p=52,200;i=block/process_s");
        }

    connections:
        mac.upperLayerOut --> { @display("ls=black;m=m,25,50,25,0"); } --> upperLayerOut;
        mac.upperLayerIn <-- { @display("ls=black;m=m,15,50,15,0"); } <-- upperLayerIn;
        mac.upperControlOut --> { @display("ls=red;m=m,75,50,75,0"); } --> upperControlOut;
        mac.upperControlIn <-- { @display("ls=red;m=m,85,0,85,0"); } <-- upperControlIn;

        ids.upperLayerOut --> { @display("ls=black;m=m,25,50,25,0"); } --> mac.lowerLayerIn;
        ids.upperLayerIn <-- { @display("ls=black;m=m,15,50,15,0"); } <-- mac.lowerLayerOut;
        ids.upperControlOut --> { @display("ls=red;m=m,75,50,75,0"); } --> mac.lowerControlIn;
        ids.upperControlIn <-- { @display("ls=red;m=m,85,0,85,0"); } <-- mac.lowerControlOut;

        phy.upperLayerOut --> { @display("ls=black;m=m,25,50,25,0"); } --> ids.lowerLayerIn;
        phy.upperLayerIn <-- { @display("ls=black;m=m,15,50,15,0"); } <-- ids.lowerLayerOut;
        phy.upperControlOut --> { @display("ls=black;m=m,75,50,75,0"); } --> ids.lowerControlIn;
        phy.upperControlIn <-- { @display("ls=red;m=m,85,0,85,0"); } <-- ids.lowerControlOut;

        radioIn --> phy.radioIn;
}

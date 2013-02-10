
package policemen.mobility;

import org.mixim.modules.mobility.ConstSpeedMobility;

simple PolicemanMobility extends ConstSpeedMobility
{
    parameters:
        @class(PolicemanMobility);
        double outskirtsWidth @unit(m) = default(0 m); // width of the outskirts without reliable reporting
}

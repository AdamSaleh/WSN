package policemen.sensors;

// Interface for sensor modules
moduleinterface ISensor
{
    parameters:
        double range @unit(m); // effective range of the sensor
        @display("i=block/classifier2");
}


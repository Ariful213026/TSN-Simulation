package tsn_simulation;

import tsn_simulation.TsnSwitch;
import tsn_simulation.TrafficGenerator;

network TsnSimulation
{
    @display("bgb=604,317");
    submodules:
        switch1: TsnSwitch {
            parameters:
                gclFilePath = default("models/GclConfig.xml");
                gclCycleTime = default(1);
                @display("p=218,135;i=block/switch");
        }
        switch2: TsnSwitch {
            parameters:
                gclFilePath = default("models/GclConfig.xml");
                gclCycleTime = default(1);
                @display("p=402,135;i=block/switch");
        }
        ttTalker: TrafficGenerator {
            parameters:
                sendInterval = default(2);
                @display("p=78,135;i=device/device");
        }
        beSender: TrafficGenerator {
            parameters:
                sendInterval = default(5);
                @display("p=78,244;i=device/device");
        }
        interferenceGen: TrafficGenerator {
            parameters:
                sendInterval = default(10);
                @display("p=78,30;i=device/device");
        }
        ttListener: TrafficGenerator {
            @display("p=510,135;i=device/device");
        }
        beReceiver: TrafficGenerator {
            @display("p=510,244;i=device/device");
        }
        interferenceReceiver: TrafficGenerator {
            @display("p=510,30;i=device/device");
        }
    connections allowunconnected:
        // Connections for Switch 1
        ttTalker.out --> switch1.in[0];
        beSender.out --> switch1.in[1];
        interferenceGen.out --> switch1.in[2];
        switch1.out[0] --> ttTalker.in;
        switch1.out[1] --> beSender.in;
        switch1.out[2] --> interferenceGen.in;

        // Connections between Switch 1 and Switch 2
        switch1.out[3] --> switch2.in[3];
        switch2.out[3] --> switch1.in[3];

        // Connections for Switch 2
        ttListener.out --> switch2.in[0];
        beReceiver.out --> switch2.in[1];
        interferenceReceiver.out --> switch2.in[2];
        switch2.out[0] --> ttListener.in;
        switch2.out[1] --> beReceiver.in;
        switch2.out[2] --> interferenceReceiver.in;
}

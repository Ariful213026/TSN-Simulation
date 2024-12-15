package tsn_simulation;  

import tsn_simulation.TsnSwitch; 
import tsn_simulation.TrafficGenerator;  

// Define a network named TsnSimulation
network TsnSimulation {
    @display("bgb=604,317"); // Set the size of the background display for the network
    
    submodules:
        // Switch 1 with GCL configuration and display properties
        switch1: TsnSwitch {
            parameters:
                gclFilePath = default("models/GclConfig.xml"); // Path to the GCL configuration file
                gclCycleTime = default(1); // Cycle time for the GCL
                @display("p=218,135;i=block/switch"); // Position and icon for the switch
        }

        // Switch 2 with similar parameters as Switch 1
        switch2: TsnSwitch {
            parameters:
                gclFilePath = default("models/GclConfig.xml");
                gclCycleTime = default(1);
                @display("p=402,135;i=block/switch");
        }

        // Time-triggered (TT) traffic source
        ttTalker: TrafficGenerator {
            parameters:
                sendInterval = default(2); // Interval at which TT traffic is generated
                @display("p=78,135;i=device/device"); // Position and icon for the traffic generator
        }

        // Best-effort (BE) traffic source
        beSender: TrafficGenerator {
            parameters:
                sendInterval = default(5); // Interval at which BE traffic is generated
                @display("p=78,244;i=device/device");
        }

        // Interference traffic source
        interferenceGen: TrafficGenerator {
            parameters:
                sendInterval = default(10); // Interval at which interference traffic is generated
                @display("p=78,30;i=device/device");
        }

        // Time-triggered (TT) traffic destination
        ttListener: TrafficGenerator {
            @display("p=510,135;i=device/device");
        }

        // Best-effort (BE) traffic destination
        beReceiver: TrafficGenerator {
            @display("p=510,244;i=device/device");
        }

        // Interference traffic destination
        interferenceReceiver: TrafficGenerator {
            @display("p=510,30;i=device/device");
        }

    connections allowunconnected:
        // Connections for Switch 1
        ttTalker.out --> switch1.in[0]; // TT traffic enters Switch 1
        beSender.out --> switch1.in[1]; // BE traffic enters Switch 1
        interferenceGen.out --> switch1.in[2]; // Interference traffic enters Switch 1
        switch1.out[0] --> ttTalker.in; // Switch 1 sends TT traffic back to ttTalker
        switch1.out[1] --> beSender.in; // Switch 1 sends BE traffic back to beSender
        switch1.out[2] --> interferenceGen.in; // Switch 1 sends interference traffic back to interferenceGen

        // Connections between Switch 1 and Switch 2
        switch1.out[3] --> switch2.in[3]; // Switch 1 connects to Switch 2
        switch2.out[3] --> switch1.in[3]; // Switch 2 connects back to Switch 1

        // Connections for Switch 2
        ttListener.out --> switch2.in[0]; // TT traffic from listener enters Switch 2
        beReceiver.out --> switch2.in[1]; // BE traffic from receiver enters Switch 2
        interferenceReceiver.out --> switch2.in[2]; // Interference traffic from receiver enters Switch 2
        switch2.out[0] --> ttListener.in; // Switch 2 sends TT traffic back to ttListener
        switch2.out[1] --> beReceiver.in; // Switch 2 sends BE traffic back to beReceiver
        switch2.out[2] --> interferenceReceiver.in; // Switch 2 sends interference traffic back to interferenceReceiver
}

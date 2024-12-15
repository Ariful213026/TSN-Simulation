package tsn_simulation;

// Define a simple module named TrafficGenerator
simple TrafficGenerator {
    parameters:
        double sendInterval;   // Time interval (in seconds) between sending consecutive packets.
                               // This controls the traffic generation rate.

    gates:
        output out;            // Output gate for sending packets to other modules.
        input in;              // Input gate for receiving packets or acknowledgments from other modules.
}

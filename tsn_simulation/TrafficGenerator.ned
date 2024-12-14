package tsn_simulation;

simple TrafficGenerator {
    parameters:
        double sendInterval;   // Interval for sending packets
    gates:
        output out;
        input in;
}

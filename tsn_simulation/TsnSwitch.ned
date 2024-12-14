package tsn_simulation;

simple TsnSwitch {
    parameters:
        string gclFilePath;    // Path to GCL configuration file
        double gclCycleTime;   // Cycle time for GCL processing
    gates:
        input in[4];
        output out[4];
}

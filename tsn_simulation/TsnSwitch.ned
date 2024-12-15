package tsn_simulation;

// Define a simple module named TsnSwitch
simple TsnSwitch {
    parameters:
        string gclFilePath;    // Path to the Gate Control List (GCL) configuration file.
                               // This file contains scheduling details for handling traffic.
        double gclCycleTime;   // Cycle time (in seconds) for processing the GCL.
                               // Determines the periodic execution of GCL entries.
    
    gates:
        input in[4];           // Array of 4 input gates for receiving data from connected modules.
        output out[4];         // Array of 4 output gates for sending data to connected modules.
}

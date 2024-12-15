#include "TsnSwitch.h"       // Include the header file for the TsnSwitch class
#include <fstream>           // Include for file operations
#include <sstream>           // Include for string stream operations

// Define the TsnSwitch module for OMNeT++
Define_Module(TsnSwitch);

// Initialize the TSN Switch
void TsnSwitch::initialize() {
    currentGclIndex = 0; // Start with the first entry in the GCL (Gate Control List)
    gclCycleTime = par("gclCycleTime"); // Retrieve the GCL cycle time parameter from the simulation configuration

    // Load the GCL from the file path provided as a parameter
    loadGcl(par("gclFilePath"));

    // Schedule the first GCL processing event
    scheduleAt(omnetpp::simTime() + gclCycleTime, new omnetpp::cMessage("ProcessGcl"));
}

// Handle incoming messages and events
void TsnSwitch::handleMessage(omnetpp::cMessage *msg) {
    // Check if the message is a "ProcessGcl" event
    if (strcmp(msg->getName(), "ProcessGcl") == 0) {
        processTraffic(); // Process the current GCL entry
        // Schedule the next GCL processing event
        scheduleAt(omnetpp::simTime() + gclCycleTime, msg);
    } else {
        // Determine which input gate the message arrived from
        int inputGateIndex = msg->getArrivalGate()->getIndex();

        // In this example, messages are sent back out on the same gate index
        int outputGateIndex = inputGateIndex;

        // Send the message through the corresponding output gate
        send(msg, "out", outputGateIndex);
    }
}

// Process the current GCL (Gate Control List) entry
void TsnSwitch::processTraffic() {
    // Log the current GCL entry being processed
    EV << "Processing GCL entry: " << gclEntries[currentGclIndex] << "\n";

    // Move to the next GCL entry, wrapping around if at the end of the list
    currentGclIndex = (currentGclIndex + 1) % gclEntries.size();
}

// Load the GCL (Gate Control List) from a file
void TsnSwitch::loadGcl(const char* gclFilePath) {
    std::ifstream file(gclFilePath); // Open the GCL file for reading
    if (!file.is_open()) {
        // Throw an error if the file cannot be opened
        throw omnetpp::cRuntimeError("Failed to load GCL file");
    }

    std::string line;
    // Read each line of the file and store it in the GCL entries vector
    while (std::getline(file, line)) {
        gclEntries.push_back(line);
    }
    file.close(); // Close the file after reading
}

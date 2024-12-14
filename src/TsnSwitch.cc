#include "TsnSwitch.h"
#include <fstream>
#include <sstream>

Define_Module(TsnSwitch);

void TsnSwitch::initialize() {
    currentGclIndex = 0;
    gclCycleTime = par("gclCycleTime");
    loadGcl(par("gclFilePath"));
    scheduleAt(omnetpp::simTime() + gclCycleTime, new omnetpp::cMessage("ProcessGcl"));
}

void TsnSwitch::handleMessage(omnetpp::cMessage *msg) {
    if (strcmp(msg->getName(), "ProcessGcl") == 0) {
        processTraffic();
        scheduleAt(omnetpp::simTime() + gclCycleTime, msg);
    } else {
        // Determine the input gate index
        int inputGateIndex = msg->getArrivalGate()->getIndex();

        // For this example, we'll send the message back on the same gate index
        int outputGateIndex = inputGateIndex;

        // Send the message through the specified output gate index
        send(msg, "out", outputGateIndex);
    }
}

void TsnSwitch::processTraffic() {
    EV << "Processing GCL entry: " << gclEntries[currentGclIndex] << "\n";
    currentGclIndex = (currentGclIndex + 1) % gclEntries.size();
}

void TsnSwitch::loadGcl(const char* gclFilePath) {
    std::ifstream file(gclFilePath);
    if (!file.is_open()) throw omnetpp::cRuntimeError("Failed to load GCL file");

    std::string line;
    while (std::getline(file, line)) {
        gclEntries.push_back(line);
    }
    file.close();
}

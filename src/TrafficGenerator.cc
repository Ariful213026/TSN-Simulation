#include "TrafficGenerator.h"

// Macro to define the module for OMNeT++ simulation
Define_Module(TrafficGenerator);

// Method to initialize the TrafficGenerator module
void TrafficGenerator::initialize() {
    // Read the 'sendInterval' parameter from the module's configuration
    sendInterval = par("sendInterval");

    // Create a self-message event to trigger traffic generation
    sendMessageEvent = new omnetpp::cMessage("SendTraffic");

    // Schedule the first traffic generation event at the current simulation time + sendInterval
    scheduleAt(omnetpp::simTime() + sendInterval, sendMessageEvent);
}

// Method to handle incoming messages and self-messages
void TrafficGenerator::handleMessage(omnetpp::cMessage *msg) {
    // Check if the received message is the self-message event
    if (msg == sendMessageEvent) {
        // Create and send a new traffic packet through the 'out' gate
        send(new omnetpp::cMessage("TrafficPacket"), "out");

        // Schedule the next traffic generation event after the 'sendInterval'
        scheduleAt(omnetpp::simTime() + sendInterval, sendMessageEvent);
    }
}

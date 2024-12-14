#include "TrafficGenerator.h"

Define_Module(TrafficGenerator);

void TrafficGenerator::initialize() {
    sendInterval = par("sendInterval");
    sendMessageEvent = new omnetpp::cMessage("SendTraffic");
    scheduleAt(omnetpp::simTime() + sendInterval, sendMessageEvent);
}

void TrafficGenerator::handleMessage(omnetpp::cMessage *msg) {
    if (msg == sendMessageEvent) {
        send(new omnetpp::cMessage("TrafficPacket"), "out");
        scheduleAt(omnetpp::simTime() + sendInterval, sendMessageEvent);
    }
}

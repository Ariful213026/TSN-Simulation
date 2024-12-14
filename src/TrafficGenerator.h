#ifndef TRAFFICGENERATOR_H
#define TRAFFICGENERATOR_H

#include <omnetpp.h>

class TrafficGenerator : public omnetpp::cSimpleModule {
private:
    omnetpp::simtime_t sendInterval;
    omnetpp::cMessage* sendMessageEvent;

protected:
    virtual void initialize() override;
    virtual void handleMessage(omnetpp::cMessage *msg) override;
};

#endif

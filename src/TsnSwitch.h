#ifndef TSNSWITCH_H
#define TSNSWITCH_H

#include <omnetpp.h>
#include <vector>

class TsnSwitch : public omnetpp::cSimpleModule {
private:
    std::vector<std::string> gclEntries; // Stores GCL configurations
    int currentGclIndex;
    omnetpp::simtime_t gclCycleTime;

    void processTraffic();

protected:
    virtual void initialize() override;
    virtual void handleMessage(omnetpp::cMessage *msg) override;

public:
    void loadGcl(const char* gclFilePath);
};

#endif

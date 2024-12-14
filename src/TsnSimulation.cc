#include <omnetpp.h>

class TsnSimulation : public omnetpp::cSimpleModule {
protected:
    virtual void initialize() override {
        EV << "TSN Simulation Initialized\n";
    }
};

Define_Module(TsnSimulation);

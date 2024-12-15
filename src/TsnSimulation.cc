#include <omnetpp.h>

// Define a class named TsnSimulation, inheriting from omnetpp::cSimpleModule
class TsnSimulation : public omnetpp::cSimpleModule {
protected:
    // Method to initialize the module
    virtual void initialize() override {
        // Log a message indicating the initialization of the TSN simulation
        EV << "TSN Simulation Initialized\n";
    }
};

// Register the TsnSimulation module with OMNeT++
Define_Module(TsnSimulation);

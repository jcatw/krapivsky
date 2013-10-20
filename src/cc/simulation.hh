#ifndef BIGNET_SIMULATION_H
#define BIGNET_SIMULATION_H

#include "common.hh"
#include "network.hh"
#include "model.hh"


namespace bignet {
  class Simulation {
  public:
    Model* model = NULL;
    Simulation(Model* model);
    virtual ~Simulation();
    
    virtual int run(int n);

    virtual Network* get_network() {return network;}
  private:
    Network* network;
  };
}
#endif

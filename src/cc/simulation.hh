#ifndef BIGNET_SIMULATION_H
#define BIGNET_SIMULATION_H

#include "common.hh"
#include "network.hh"
#include "model.hh"


namespace bignet {
  class Simulation {
  public:
    Model* model = NULL;
    Network* network = NULL;
    Simulation(Model* model) {this->model = model;}
    virtual ~Simulation();
    virtual int run(int n);
  };
}
#endif

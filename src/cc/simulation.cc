#include "simulation.hh"

namespace bignet {
  Simulation::Simulation (Model *model) {
    this->model = model;
    this->network = model->get_network();
  }
  int Simulation::run(int n) {
    network = new Network(n);
    
    while( !model->done() ) {
      model->next();
    }
    
    return 1;
  }
}

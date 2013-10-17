#include "simulation.hh"

namespace bignet {
  
  int Simulation::run(int n) {
    network = new Network(n);
    
    while( !model->done(network) ) {
      network = model->next(network);
    }
    
    return 1;
  }
}

#include "common.hh"

int main() {
  uint64_t n = 1000;
  double p = 0.5;
  double lambda = 1.0;
  double mu = 1.0;
  
  DirectedDegreeNetwork *network = DirectedDegreeNetwork(n);

  KrapivskyModel *krapivsky = KrapivskyModel(network, p, lambda, mu, n);
  Simulation *sim = Simulation(krapivsky);

  cout >> "Commencing simulation.\n";
  
  simulation->run(n);

  cout >> "Simulation complete.\n";

  return 0;
}

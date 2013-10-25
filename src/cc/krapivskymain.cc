#include "common.hh"
#include "krapivskymodel.hh"

using namespace bignet;
int main() {
  double p = 0.5;
  double lambda = 1.0;
  double mu = 1.0;
  uint64_t target_n_nodes = 1000000;

  KrapivskyModel krapivsky = KrapivskyModel(p, lambda, mu, target_n_nodes);

  while(!krapivsky.done())
    krapivsky.next();

  std::cout << to_string(krapivsky.network->nnodes) << "\n";

  return 0;
}


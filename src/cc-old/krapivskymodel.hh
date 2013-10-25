#ifndef BIGNET_KRAPIVSKYMODEL_H
#define BIGNET_KRAPIVSKYMODEL_H

#include "common.hh"
#include "model.hh"
#include "network.hh"
#include "bstreap.hh"
#include "indegreebstreapitem.hh"
#include "outdegreebstreapitem.hh"

namespace bignet {
  class KrapivskyModel : private Model {
  public:
    KrapivskyModel(Network *network_seed, double p, double lambda, double mu, uint64_t target_n_nodes);

    // implementation of methods inherited from Model
    void next();
    int done();

  private:
    uint64_t target_n_nodes;
    Bstreap *in_degree_set = new Bstreap();
    Bstreap *out_degree_set = new Bstreap();

    // inherited from Model
    //Network *network;

    void construct_indices(Network* network);
    double p;
    double lambda;
    double mu;
  };
}

#endif /* BIGNET_KRAPIVSKYMODEL_H */

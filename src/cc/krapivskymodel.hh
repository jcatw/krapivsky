#ifndef BIGNET_KRAPIVSKYMODEL_H
#define BIGNET_KRAPIVSKYMODEL_H

#include "common.hh"
#include "degreenode.hh"
#include "network.hh"
#include "bstreap.hh"


namespace bignet {
  class KrapivskyModel {
  public:
    double p, lambda, mu;
    uint64_t target_n_nodes;
    Bstreap<DegreeNode> *in_degree_set;
    Bstreap<DegreeNode> *out_degree_set;
    Network<DegreeNode> *network;
    
    KrapivskyModel(double p, double lambda, double mu, uint64_t target_n_nodes);

    void next();
    bool done();
  };
}

#endif /* BIGNET_KRAPIVSKYMODEL_H */

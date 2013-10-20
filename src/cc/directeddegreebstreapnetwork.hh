#ifndef BIGNET_DIRECTEDDEGREEBSTREAPNETWORK_H
#define BIGNET_DIRECTEDDEGREEBSTREAPNETWORK_H

#include "common.hh"
#include "directeddegreenetwork.hh"
#include "bstreap.hh"

namespace bignet {
  class DirectedDegreeBstreapNetwork : private DirectedDegreeNetwork {
  public:
    Bstreap* get_in_degree_set() { return in_degree_set; }
    Bstreap* get_out_degree_set() { return out_degree_set; }

  private:
    void seed();
    //InDegreeBstreapItem *wrap_node_in_degree(DegreeNode* node);
    //OutDegreeBstreapItem *wrap_node_out_degree(DegreeNode* node);
  };
}

#endif /* BIGNET_DIRECTEDDEGREEBSTREAPNETWORK_H */

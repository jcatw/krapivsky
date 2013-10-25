#include "directeddegreebstreapnetwork.hh"

namespace bignet {
  //InDegreeBstreapItem *DirectedDegreeBstreapNetwork::wrap_node_in_degree(DegreeNode* node) {
  //  return new InDegreeBstreapItem(node);
  //}
  //InDegreeBstreapItem *DirectedDegreeBstreapNetwork::wrap_node_out_degree(DegreeNode* node) {
  //  return new OutDegreeBstreapItem(node);
  //}

  void DirectedDegreeBstreapNetwork::seed() {
    Network::seed();
    for (int i=0; i<nnodes; i++) {
      get_in_degree_set->insert(node_array[i],fitness)
    }
  }
}

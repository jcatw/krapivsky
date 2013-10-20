#include "krapivskymodel.hh"

namespace bignet {
  KrapivskyModel::KrapivskyModel(Network *network_seed, double p, double lambda, double mu, uint64_t target_n_nodes) {
    this->p = p;
    this->lambda = lambda;
    this->mu = mu;
    this->target_n_nodes = target_n_nodes;

    construct_indices(network_seed);
    this->network = network_seed;
  }

  void KrapivskyModel::construct_indices(Network* network) {
    for (int i=0;i<network->nnodes;i++) {
      in_degree_set->insert( new InDegreeBstreapItem( (DegreeNode*) network->node_array[i], lambda ) );
      out_degree_set->insert( new OutDegreeBstreapItem( (DegreeNode*) network->node_array[i], mu ) );
    }
  }

  void KrapivskyModel::next() {
    InDegreeBstreapItem *sampled_in_degree_item;
    OutDegreeBstreapItem *sampled_out_degree_item;
    
    DegreeNode *sampled_in_degree_node;
    DegreeNode *sampled_out_degree_node;
    DegreeNode *new_node;

    double uniform_sample = uniform_random();

    if (uniform_sample < p) {  // we are taking a node step
      new_node = new DegreeNode((uint64_t) network->nnodes);
      sampled_in_degree_item = in_degree_set->sample_destructive();
      sampled_in_degree_node = (DegreeNode*) in_degree_set->sample_destructive();

      new_node->add_edge(sampled_in_degree_node);

      in_degree_set->insert(sampled_in_degree_node);

      in_degree_set->insert(new_node);
      out_degree_set->insert(new_node);
    }
    else {  // we are taking an edge step
      sampled_in_degree_node = (DegreeNode*) in_degree_set->sample_destructive();
      sampled_out_degree_node = (DegreeNode*) out_degree_set->sample_destructive();

      sampled_out_degree_node->add_edge(sampled_in_degree_node);

      in_degree_set->insert(sampled_in_degree_node);
      out_degree_set->insert(sampled_out_degree_node);
    }
  }

  int KrapivskyModel::done() {
    return (network->nnodes >= target_n_nodes);
  }
}

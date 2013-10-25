#include "krapivskymodel.hh"

namespace bignet {
  KrapivskyModel::KrapivskyModel(double p, double lambda, double mu, uint64_t target_n_nodes) : \
    p(p), lambda(lambda), mu(mu), target_n_nodes(target_n_nodes) {

    in_degree_set = new Bstreap<DegreeNode>();
    out_degree_set = new Bstreap<DegreeNode>();
       
    network = new Network<DegreeNode>(target_n_nodes);

    //#TODO
    in_degree_set->insert((InDegreeNode*) network->node_array[0], lambda);
    in_degree_set->insert((InDegreeNode*) network->node_array[1], lambda);
    in_degree_set->insert((InDegreeNode*) network->node_array[2], lambda);

    out_degree_set->insert((OutDegreeNode*) network->node_array[0], mu);
    out_degree_set->insert((OutDegreeNode*) network->node_array[1], mu);
    out_degree_set->insert((OutDegreeNode*) network->node_array[2], mu);
                          
  }

  void KrapivskyModel::next() {
    double uniform_sample = uniform_random_double();

    InDegreeNode *sampled_indeg_node;
    OutDegreeNode *sampled_outdeg_node;
    
    if (uniform_sample < p) {
      DegreeNode *new_node = new DegreeNode(network->nnodes);
      sampled_indeg_node = (InDegreeNode*) in_degree_set->sample_destructive();

      new_node->add_edge(sampled_indeg_node);

      network->add_node(new_node);

      in_degree_set->insert(sampled_indeg_node, lambda);

      out_degree_set->insert((OutDegreeNode*) new_node, mu);
      in_degree_set->insert((InDegreeNode*) new_node, lambda);
    }
    else {
      sampled_indeg_node = (InDegreeNode*) in_degree_set->sample_destructive();
      sampled_outdeg_node = (OutDegreeNode*) out_degree_set->sample_destructive();

      sampled_outdeg_node->add_edge(sampled_indeg_node);

      in_degree_set->insert(sampled_indeg_node, lambda);
      out_degree_set->insert(sampled_outdeg_node, mu);
    }
  }

  bool KrapivskyModel::done() {return network->nnodes >= target_n_nodes;}
  
}

#include "directeddegreenetwork.hh"

namespace bignet {
  //void DirectedDegreeNetwork::add_node(Node* node) {
  //  node_array[nnodes] = node;
  //  get_in_degree_set()->insert( wrap_node(node) );
  //  get_out_degree_set()->insert( wrap_node(node) );
  //}
  
  void DirectedDegreeNetwork::seed() {
    DegreeNode *node0 = new DegreeNode((uint64_t) 0);
    DegreeNode *node1 = new DegreeNode((uint64_t) 1);
    DegreeNode *node2 = new DegreeNode((uint64_t) 2);
    
    add_node(node0);
    add_node(node1);
    add_node(node2);
    
    node0->add_edge(node1);
    node0->add_edge(node2);
    node1->add_edge(node2);
  }

  //DirectedDegreeNetwork::~DirectedDegreeNetwork() {
  //  delete in_degree_set;
  //  delete out_degree_set;
  //  Network::~Network();
  //}
}

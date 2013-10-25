#ifndef BIGNET_NETWORK_H
#define BIGNET_NETWORK_H

#include "common.hh"
#include <vector>

using namespace std;

namespace bignet {
  template<class T> class Network {
  public:
    uint64_t nnodes;
    uint64_t max_nodes;
    vector<T*> node_array;
    
    Network(uint64_t n);
    void add_node(T *node);
    
  };
//template<class T> Network<T>::Network(int n);
//template<class T> void Network<T>::add_node(T *node);
template<class T> Network<T>::Network(uint64_t n) : nnodes(3), max_nodes(n), node_array(n,NULL) {
    T *node0 = new T(0);
    T *node1 = new T(1);
    T *node2 = new T(2);

    node1->add_edge(node0);
    node2->add_edge(node1);
    node2->add_edge(node2);

    node_array[0] = node0;
    node_array[1] = node1;
    node_array[2] = node2;
  }
    
  template<class T> void Network<T>::add_node(T *node) {
    node_array[nnodes] = node;
    nnodes++;
  }
}

#endif /* BIGNET_NETWORK_H */

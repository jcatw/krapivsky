#ifndef BIGNET_NETWORK_H
#define BIGNET_NETWORK_H

#include "common.hh"
#include "node.hh"

namespace bignet {
  class Network {
  public:
    virtual ~Network();
    Network(int n);
    virtual void add_node(Node *node);
    
  private:
    virtual void seed();

    int nnodes = 0;
    Node** node_array = NULL;
    int final_size;
  };
}
#endif

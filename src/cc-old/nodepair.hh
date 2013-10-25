#ifndef BIGNET_NODEPAIR_H
#define BIGNET_NODEPAIR_H

#include "common.hh"
#include "node.hh"

namespace bignet {
  // a NodePair is a cons cell for nodes.
  // Note that deleting a NodePair does not
  // delete the nodes that it contains.
  class NodePair {
  public:
    Node* node = NULL;
    NodePair* next = NULL;

    NodePair();
    NodePair(Node* node);
    NodePair(Node* node, NodePair* next);

    ~NodePair();  
  };
}
#endif
    

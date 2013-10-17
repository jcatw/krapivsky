#include "nodepair.hh"

namespace bignet {
  NodePair::NodePair(Node* node) {this->node = node;}
  NodePair::NodePair(Node* node, NodePair* next) {
    this->node = node;
    this->next = next;
  }

  // free the chain of pairs, but do not free the nodes
  NodePair::~NodePair() {
    if(next)
      delete next;
  }
    
}

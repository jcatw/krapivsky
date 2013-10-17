#include "node.hh"

namespace bignet {
  void Node::add_edge(Node* to) {
    NodePair* new_head = new NodePair(to, adjacency_list);
    adjacency_list = new_head;
  }
}

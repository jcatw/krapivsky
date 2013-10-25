#include "node.hh"

namespace bignet {
  Node::Node() {
    this->id = 0;
  }
  Node::Node(uint64_t id) {
    this->id = id;
  }
  void Node::add_edge(Node* to) {
    NodePair* new_head = new NodePair(to, adjacency_list);
    adjacency_list = new_head;
  }
}

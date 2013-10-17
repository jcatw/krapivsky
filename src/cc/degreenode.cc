namespace bignet {
  void DegreeNode::add_edge(Node* to) {
    Node::add_edge(to);
    out_degree++;
    ((DegreeNode*) to)->in_degree++;
  }
}



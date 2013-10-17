#include "network.hh"

namespace bignet {

  //assumes a final size is known. fine for the model at hand, will
  //want to generalize later.
  Network::Network(int final_size) {
    node_array = (Node**) malloc(final_size * sizeof(Node*));
    seed();
  }

  //free all of the nodes upon deletion
  Network::~Network() {
    int i = 0;
    for(i=0;i<final_size;i++){
      delete node_array[i];
    }
    free(node_array);
  }

  void Network::add_node(Node* node) {
    node_array[nnodes] = node;
    nnodes++;
  }

  // networks are initialized to the following by default:
  //
  // 0 --> 1
  // 0 --> 2
  // 1 --> 2
  void Network::seed() {
    Node *node0 = new Node(0);
    Node *node1 = new Node(1);
    Node *node2 = new Node(2);

    add_node(node0);
    add_node(node1);
    add_node(node2);

    node0->add_edge(node1);
    node0->add_edge(node2);
    node1->add_edge(node2);
  }
}

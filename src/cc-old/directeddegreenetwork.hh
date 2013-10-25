#ifndef BIGNET_DIRECTEDDEGREENETWORK_H
#define BIGNET_DIRECTEDDEGREENETWORK_H

#include "common.hh"
#include "network.hh"
#include "nodeset.hh"
#include "degreenode.hh"

namespace bignet {
  class DirectedDegreeNetwork : public Network {
  public:
    //virtual ~DirectedDegreeNetwork();
    //virtual NodeSet* get_in_degree_set()=0;
    //virtual NodeSet* get_out_degree_set()=0; 

    DegreeNode** node_array = NULL;
  private:
    void seed();

    //virtual SetItem *wrap_node_in_degree(Node* node)=0;
    //virtual SetItem *wrap_node_out_degree(Node* node)=0;
  };
}

#endif /* BIGNET_DIRECTEDDEGREENETWORK_H */

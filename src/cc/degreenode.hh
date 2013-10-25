#ifndef BIGNET_DEGREENODE_H
#define BIGNET_DEGREENODE_H

#include "common.hh"
#include <list>

using namespace std;

namespace bignet {
  class DegreeNode {
  public:
    const uint64_t id;
    //const double fitness;
    
    uint64_t in_degree;
    uint64_t out_degree;

    list<DegreeNode*> adjacency_list;
    
    DegreeNode(uint64_t id);

    void add_edge (DegreeNode* to);
    virtual uint64_t get_value() {return in_degree + out_degree;}
    //float get_fitness() {return fitness;}
  };
}
#endif /* BIGNET_DEGREENODE_H */

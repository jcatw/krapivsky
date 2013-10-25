#ifndef BIGNET_NODELIST_H
#define BIGNET_NODELIST_H

#include "common.hh"
#include "nodepair.hh"

namespace bignet {
  class NodeList {    
  public:
    NodePair* head = NULL;
    NodeList();
    NodeList(NodePair* head) {this->head = head;}
  };
}
#endif

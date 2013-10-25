#ifndef BIGNET_NODESET_H
#define BIGNET_NODESET_H

#include "common.hh"
#include "setitem.hh"
#include "node.hh"

namespace bignet {
  // NodeSet is a purely virtual (abstract) class which specifies the
  // the interface for inserting, deleting, and sampling from
  // collections of nodes.
  class NodeSet {
  public:
    virtual ~NodeSet();  // I gather a virtual destructor is needed; c++ is confuse.
    //virtual void insert(SetItem*) =0;  // this is just the craziest way to express anything
    //virtual Node* sample() =0;
    //virtual Node* sample_destructive() =0;
    //virtual void remove_item(SetItem* item) =0;
  };
}
#endif

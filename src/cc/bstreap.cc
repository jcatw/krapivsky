#include "bstreap.hh"

namespace bignet {
  void Bstreap::insert(BstreapItem *item) {
    // insert item
    if (root == NULL ) {
      root = item;
    }
    else {
      root->insert(item);
    }

    //update metadata
    n_items++;
    total_mass += item->get_my_mass();

  }
  BstreapItem* Bstreap::sample() {
    double uniform_sample;
    if (root == NULL) {
      return NULL;
    }
    uniform_sample = uniform_random();
    return root->sample(this,uniform_sample,0.0);
  }
  BstreapItem* Bstreap::sample_destructive() {
    double uniform_sample;
    BstreapItem *returned_item;
    //Node* returned_node;
    
    if (root == NULL) {
      return NULL;
    }
    uniform_sample = uniform_random();
    returned_item = root->sample_destructive(this, uniform_sample, 0.0);
    //returned_node = returned_item->node;
    
    n_items--;
    total_mass -= returned_item->get_my_mass();
    remove_item(returned_item);
    
    return returned_item;
    
  }

  void Bstreap::remove_item(BstreapItem *item) {
    item->remove(this);
    
  }
}

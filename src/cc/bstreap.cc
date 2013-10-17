namespace bignet {
  void Bstreap::insert(BstreapItem *item) {
    // insert item
    if (root == NULL ) {
      root = item;
    }
    else {
      root.insert(item);
    }

    //update metadata
    n_items++;
    total += item->get_my_mass();

  }
  BstreapItem Bstreap::sample() {
    double uniform_sample;
    if (root == NULL) {
      return NULL;
    }
    uniform_sample = uniform_random();
    root->sample(uniform_sample);
  }
  BstreapItem Bstreap::sample_destructive() {
    double uniform_sample;
    if (root == NULL) {
      return NULL;
    }
    uniform_sample = uniform_random();
    root->sample_destructive(uniform_sample);
  }
}

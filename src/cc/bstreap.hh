#ifndef BIGNET_BSTREAP_H
#define BIGNET_BSTREAP_H

#include "common.hh"
#include "degreenode.hh"
#include "indegreenode.hh"
#include "outdegreenode.hh"

namespace bignet {
  template<class T> class BstreapNode {
  public:
    Bstreap<T> *bstreap;
    double node_mass, subtree_mass;
    double priority;

    T *contents;
    BstreapNode *left;
    BstreapNode *right;
    BstreapNode *parent;

    BstreapNode(Bstreap<T> *bstreap, T *contents, uint64_t value, double offset);
    ~BstreapNode();

    // insert and sample boxed data at the node level
    BstreapNode *insert(BstreapNode* node);

    BstreapNode *sample(double uniform_sample, double accumulated_mass);
    BstreapNode *sample_destructive(double uniform_sample, double accumulated_mass);

    virtual double generate_priority() {return random_double();}
    virtual bool go_left_comparison(BstreapNode* node);
  };
  
  template<class T> class Bstreap {
  public:
    int n_items;
    double total_mass;
    BstreapNode<T> *root = NULL;

    Bstreap() : n_items(0), total_mass(0.) {};

    // insert and sample unboxed data at interface level
    void insert(T *contents, double fitness);

    T *sample();
    T *sample_destructive();

    // remove boxed data
    void remove_node(BstreapNode<T> *node);

    static void rotate_left(BstreapNode<T> *&bstreapitem);
    static void rotate_right(BstreapNode<T> *&bstreapitem);
  };

  // BstreapNode definitions
  template<class T> BstreapNode<T>::BstreapNode(Bstreap<T> *bstreap, T *contents, uint64_t value, double offset) {
    this->bstreap = bstreap;
    this->contents = contents;
    node_mass = (double) value + offset;
    subtree_mass = node_mass;
    left = NULL;
    right = NULL;
    parent = NULL;

    priority = generate_priority();
  }

  template<class T> BstreapNode<T>::~BstreapNode() {
    if(parent != NULL) {
      if (parent->left == this)
        parent->left = NULL;
      else
        parent->right = NULL; 
    }
  }

  template<class T> BstreapNode<T> bool::go_left_comparison(BstreapNode* node) {
    return node->node_mass < this->node_mass;
  }

  template<class T> BstreapNode<T> *BstreapNode<T>::insert(BstreapNode* node) {
    // note: the 'which way' comparison needs to be abstracted;
    // just want to get things running first
    if (go_left_comparison(node)) {
      //if (node->node_mass < this->node_mass) { //insert left
      if (this->left == NULL) { //nothing there
        node->parent = this;
        return this->left = node;
      }
      else  //something there
        return this->left->insert(node);
    }
    else { //insert right
      if (this->right == NULL) {  //nothing there
        node->parent = this;
        return this->right = node;
      }
      else  //something there
        return this->right->insert(node); 
    }
    // note: rotations handled by Bstreap::insert
  }

  template<class T> BstreapNode<T> *BstreapNode<T>::sample(double uniform_sample, double accumulated_mass) {
    // sample left?
    if (left != NULL) {
      if (uniform_sample < (accumulated_mass + left->subtree_mass) / bstreap->total_mass)
        return left->sample(uniform_sample, accumulated_mass);
      accumulated_mass += left->subtree_mass;
    }

    // sample this?
    accumulated_mass += this->node_mass;
    if (uniform_sample < accumulated_mass / bstreap->total_mass)
      return this;

    // sample right?
    if (right != NULL)
      return right->sample(uniform_sample, accumulated_mass);

    // failed to sample
    return NULL; //should not happen!
  }

  template<class T> BstreapNode<T> *BstreapNode<T>::sample_destructive(double uniform_sample, double accumulated_mass) {
    BstreapNode *sampled_node;
    // sample left?
    if (left != NULL) {
      if (uniform_sample < (accumulated_mass + left->subtree_mass) / bstreap->total_mass) {
        sampled_node = left->sample(uniform_sample, accumulated_mass);
        this->subtree_mass -= sampled_node->node_mass;
        return sampled_node;
      }
      accumulated_mass += left->subtree_mass;
    }

    // sample this?
    accumulated_mass += this->node_mass;
    if (uniform_sample < accumulated_mass / bstreap->total_mass)
      return this;

    // sample right?
    if (right != NULL) {
      sampled_node = right->sample(uniform_sample, accumulated_mass);
      this->subtree_mass -= sampled_node->node_mass;
      return sampled_node;
    }

    // failed to sample
    return NULL; //should not happen!
  }


  // Bstreap definitions
  template<class T> void Bstreap<T>::insert(T *contents, double fitness) {
    BstreapNode<T> *node = new BstreapNode<T>(this, contents, contents->get_value(), fitness);

    if(root == NULL)
      root = node;
    else {
      BstreapNode<T> *insertion_point = root->insert(node);
      
      if(insertion_point->left == node) {
        if(node->priority > insertion_point->priority)
          rotate_right(insertion_point);
      }
      else { //insertion_point->right == node
        if(node->priority > insertion_point->priority)
          rotate_left(insertion_point);
      }
    }
  }

  template<class T> T *Bstreap<T>::sample() {
    if (root == NULL)
      return NULL;

    double uniform_sample = uniform_random_double();

    BstreapNode<T> *sampled_node = root->sample(uniform_sample, 0.);

    return sampled_node->contents;
  }

  template<class T> T *Bstreap<T>::sample_destructive() {
    if (root == NULL)
      return NULL;

    double uniform_sample = uniform_random_double();

    BstreapNode<T> *sampled_node = root->sample_destructive(uniform_sample, 0.);
    T *contents = sampled_node->contents;

    remove_node(sampled_node);

    return contents;
  }

  template<class T> void Bstreap<T>::remove_node(BstreapNode<T> *node) {
    while(!(node->left == NULL && node->right == NULL)) {
      if(node->left == NULL) {
        rotate_left(node);
        node = node->left;
      }
      else if (node->right == NULL) {
        rotate_right(node);
        node = node->right;
      }
      else if (node->left->priority > node->right->priority) {
        rotate_right(node);
        node = node->right;
      }
      else {
        rotate_left(node);
        node = node->left;
      }
    }
    if(node == root) {
      root = NULL;
    }
    delete node;
  }

  template<class T> void Bstreap<T>::rotate_left(BstreapNode<T> *& bstreapitem) {
    BstreapNode<T> *P;
    BstreapNode<T> *Q;
    BstreapNode<T> *Q_left;

    double P_total;
    double fulltotal = bstreapitem->subtree_mass;

    P = bstreapitem;
    Q = P->right;
    if (Q != NULL) {
      Q_left = Q->left;
    }
    else {
      Q_left = NULL;
    }
    bstreapitem = Q;
    bstreapitem->subtree_mass = fulltotal;
    
    P->right = Q_left;

    P_total = fulltotal;
    if (Q != NULL) {
      P_total -= Q->node_mass;
      if (Q->right != NULL) {
        P_total -= Q->right->subtree_mass;
      }
    }
    //((BstreapItem)* P)->set_total_mass(P_total);
    P->subtree_mass = P_total;
    bstreapitem->left = P;
  }

  template<class T> void Bstreap<T>::rotate_right(BstreapNode<T> *& bstreapitem) {
    BstreapNode<T> *Q;
    BstreapNode<T> *P;
    BstreapNode<T> *P_right;

    double Q_total;
    //double fulltotal = bstreapitem->subtree_mass;
    double fulltotal = bstreapitem->subtree_mass;
    
    Q = bstreapitem;
    P = Q->left;
    if (P != NULL) {
      P_right = P->right;
    }
    else {
      P_right = NULL;
    }
    bstreapitem = P;
    bstreapitem->subtree_mass = fulltotal;

    Q->left = P_right;
    Q_total = fulltotal;
    if (P != NULL) {
      Q_total -= P->node_mass;
      if (P->left != NULL) {
        Q_total -= P->left->subtree_mass;
      }
    }
    //Q->set_total_mass(Q_total);
    Q->subtree_mass = Q_total;
    bstreapitem->right = Q;
  }
}

#endif /* BIGNET_BSTREAP_H */

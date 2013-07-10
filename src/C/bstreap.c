#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include "bstreap.h"

bstreap* bstreap_new() {
  bstreap *new_bstreap_p =  (bstreap*) malloc(sizeof(bstreap));
  new_bstreap_p->n_items = 0;
  new_bstreap_p->total = 0.;
  new_bstreap_p->root = NULL;

  return new_bstreap_p;
}

knode* kalloc(int id, int in_degree, int out_degree) {
  knode *knode_p = (knode*) malloc(sizeof(knode));
  knode_p->id = id;
  knode_p->in_degree = in_degree;
  knode_p->out_degree = out_degree;
  knode_p->adjacency_list = NULL;

  return knode_p;
}

void add_adjacent_node(knode *knode_from, knode *knode_to) {
  knode_list *tmp;
  tmp = knode_from->adjacency_list;
  knode_from->adjacency_list = (knode_list*) malloc(sizeof(knode_list));
  knode_from->adjacency_list->knode_p = knode_to;
  knode_from->adjacency_list->next = tmp;
}

treapnode* talloc(knode* knode_p, int value, double offset) {
  treapnode *new_treapnode_p = (treapnode*) malloc(sizeof(treapnode));

  new_treapnode_p->value = value;
  new_treapnode_p->priority = rand();
  new_treapnode_p->count = 1;
  new_treapnode_p->offset = offset;
  new_treapnode_p->total = offset + (double) value;
  new_treapnode_p->knode_p = knode_p;
  new_treapnode_p->left = NULL;
  new_treapnode_p->right = NULL;
  //new_treapnode_p->knode_list_p = (knode_list*) malloc(sizeof(knode_list));
  //new_treapnode_p->knode_list_p->knode_p = knode_p;
  //new_treapnode_p->knode_list_p->next = NULL;

  return new_treapnode_p;
}

//knode* sample_knode(treapnode *treapnode_p) {
//  int i;
//  knode_list *knode_list_p;
//  int which = rand() % treapnode_p->count;
//
//  knode_list_p = treapnode_p->knode_list_p;
//  for(i=0;i<which;i++)
//    knode_list_p = knode_list_p->next;
//
//  return knode_list_p->knode_p;
//}
//
//knode* remove_random_knode(treapnode *treapnode_p) {
//  int i;
//  knode_list *knode_list_p, *prev, *next;
//  knode *knode_p;
//  int which = rand() % treapnode_p->count;
//
//  (treapnode_p->count)--;
//
//  if(which == 0) { 
//    knode_list_p = treapnode_p->knode_list_p;
//    treapnode_p->knode_list_p = knode_list_p->next;
//    knode_p = knode_list_p->knode_p;
//    free(knode_list_p);
//  }
//  else {
//    prev = treapnode_p->knode_list_p;
//    next = prev->next;
//    for(i=1;i<which;i++) {
//      prev = next;
//      next = prev->next;
//    }
//    knode_list_p = next->next;
//    knode_p = next->knode_p;
//    prev->next = knode_list_p;
//    free(next);
//  }
//  return knode_p;
//}

void rotate_right(treapnode** treapnode_pp) {
  treapnode *Q;
  treapnode *P;
  treapnode *P_right;
  double fulltotal = (*treapnode_pp)->total;
  Q = *treapnode_pp;
  P = Q->left;
  if (P != NULL)
    P_right = P->right;
  else
    P_right = NULL;
  *treapnode_pp = P;
  (*treapnode_pp)->total = fulltotal;
  Q->left = P_right;
  Q->total = fulltotal;
  if (P != NULL) {
    Q->total -= (double) P->count * (P->offset + (double) P->value);
    if (P->left != NULL)
      Q->total -= P->left->total;
  }
  (*treapnode_pp)->right = Q;
}

void rotate_left(treapnode** treapnode_pp) {
  treapnode *P;
  treapnode *Q;
  treapnode *Q_left;
  double fulltotal = (*treapnode_pp)->total;
  P = *treapnode_pp;
  Q = P->right;
  if (Q != NULL)
    Q_left = Q->left;
  else
    Q_left = NULL;
  *treapnode_pp = Q;
  (*treapnode_pp)->total = fulltotal;
  P->right = Q_left;
  P->total = fulltotal;
  if (Q != NULL) {
    P->total -= (double) Q->count * (Q->offset + (double) Q->value);
    if (Q->right != NULL)
      P->total -= Q->right->total;
  }
  (*treapnode_pp)->left = P;
}

void bstreap_insert(bstreap *bstreap_p, knode *knode_p, int value, double offset) {
  if(bstreap_p->root == NULL) {
    bstreap_p->root = talloc(knode_p, value, offset);    
    bstreap_p->n_items++;
    bstreap_p->total += offset + (double) value;    
  }
  else
    bstreap_insert_help(bstreap_p, bstreap_p->root, knode_p, value, offset, NULL, 0);
}

void bstreap_insert_help(bstreap* bstreap_p, treapnode *treapnode_p, knode *knode_p, int value, double offset, treapnode *parent, int left) {
  //knode_list *temp_knode_list_p;
  treapnode_p->total += offset + (double) value;
  //if(treapnode_p->value == value) {
  //  treapnode_p->count++;
  //  bstreap_p->total += offset + (double) value;
  //  bstreap_p->n_items++;
  //  temp_knode_list_p = treapnode_p->knode_list_p;
  //  treapnode_p->knode_list_p = (knode_list*) malloc(sizeof(knode_list));
  //  treapnode_p->knode_list_p->knode_p = knode_p;
  //  treapnode_p->knode_list_p->next = temp_knode_list_p;
  //  return;
  //}
  //else if (value < treapnode_p->value) {
  if (value <= treapnode_p->value) {
    if(treapnode_p->left == NULL) {
      treapnode_p->left = talloc(knode_p, value, offset);
      bstreap_p->total += offset + (double) value;
      bstreap_p->n_items++;
      if (treapnode_p->left->priority > treapnode_p->priority) {
	rotate_right(&treapnode_p);

	if (parent != NULL) {
	  if (left)
	    parent->left = treapnode_p;
	  else
	    parent->right = treapnode_p;
	}
	else 
	  bstreap_p->root = treapnode_p;
	
      }
      return;
    }
    else {
      bstreap_insert_help(bstreap_p,treapnode_p->left, knode_p, value, offset, treapnode_p, 1);
      if (treapnode_p->left->priority > treapnode_p->priority) {
	rotate_right(&treapnode_p);
	if (parent != NULL) {
	  if (left)
	    parent->left = treapnode_p;
	  else
	    parent->right = treapnode_p;
	}
	else
	  bstreap_p->root = treapnode_p;
      }
    }
    
  }
  else {
    if(treapnode_p->right == NULL) {
      treapnode_p->right = talloc(knode_p, value, offset);
      bstreap_p->total += offset + (double) value;
      bstreap_p->n_items++;
      if (treapnode_p->right->priority > treapnode_p->priority) {
	rotate_left(&treapnode_p);
	if (parent != NULL) {
	  if (left)
	    parent->left = treapnode_p;
	  else
	    parent->right = treapnode_p;
	}
	else
	  bstreap_p->root = treapnode_p;
      }          
      return;
    }
    else {
      bstreap_insert_help(bstreap_p,treapnode_p->right, knode_p, value, offset, treapnode_p, 0);
      if (treapnode_p->right->priority > treapnode_p->priority) {
	rotate_left(&treapnode_p);
	if (parent != NULL) {
	  if (left)
	    parent->left = treapnode_p;
	  else
	    parent->right = treapnode_p;
	}
	else
	  bstreap_p->root = treapnode_p;
      }          
    }
    
  }
}

//knode* bstreap_decrement(bstreap *bstreap_p, int value, double offset) {
//  bstreap_p->n_items--;
//  bstreap_p->total -= offset + (double) value;
//  bstreap_decrement_helper(bstreap_p->root, value, offset);
//}
//
//knode* bstreap_decrement_helper(treapnode *treapnode_p, int value, double offset) {
//  knode *decremented_knode_p;
//  treapnode_p->total -= offset + (double) value;
//
//  if(treapnode_p->value == value) {
//    return remove_random_knode(treapnode_p);
//  }
//  else if (value < treapnode_p->value) {
//    if (treapnode_p->left != NULL)
//      return bstreap_decrement_helper(treapnode_p->left, value, offset);
//  }
//  else {
//    if (treapnode_p->right != NULL)
//      return bstreap_decrement_helper(treapnode_p->right, value, offset);
//  }
//}

knode* bstreap_sample(bstreap *bstreap_p) {
  double uniform_sample = rand() / (double)RAND_MAX;
  return bstreap_sample_helper(bstreap_p, bstreap_p->root, 0.0, uniform_sample);
}

knode* bstreap_sample_helper(bstreap *bstreap_p, treapnode *treapnode_p, double total, double uniform_sample) {
  if(treapnode_p->left != NULL) {
    if(uniform_sample < (total + ((double) treapnode_p->left->total)) / bstreap_p->total)
      return bstreap_sample_helper(bstreap_p, treapnode_p->left, total, uniform_sample);
    total += (double) treapnode_p->left->total;
  }
  total += (double) treapnode_p->count * (treapnode_p->offset + (double) treapnode_p->value);
  if(uniform_sample < total / bstreap_p->total)
    //return sample_knode(treapnode_p);
    return treapnode_p->knode_p;
  if(treapnode_p->right != NULL)
    return bstreap_sample_helper(bstreap_p, treapnode_p->right, total, uniform_sample);
  return NULL; //should not happen!
}

knode* bstreap_sample_destructive(bstreap *bstreap_p, double offset, int in) {
  knode *returned_knode_p;
  double uniform_sample = rand() / (double)RAND_MAX;
  bstreap_p->n_items--;
  returned_knode_p = bstreap_sample_destructive_helper(bstreap_p, bstreap_p->root, 0.0, uniform_sample, offset, in);
  if (in)
    bstreap_p->total -= offset + (double) returned_knode_p->in_degree;
  else
    bstreap_p->total -= offset + (double) returned_knode_p->out_degree;
  return returned_knode_p;
}

knode* bstreap_sample_destructive_helper(bstreap *bstreap_p, treapnode *treapnode_p, double total, double uniform_sample, double offset, int in) {
  knode *returned_knode_p;
  if(treapnode_p->left != NULL) {
    if(uniform_sample < (total + ((double) treapnode_p->left->total)) / bstreap_p->total) {
      returned_knode_p = bstreap_sample_destructive_helper(bstreap_p, treapnode_p->left, total, uniform_sample, offset, in);
      if (in)
	treapnode_p->total -= offset + (double) returned_knode_p->in_degree;
      else
	treapnode_p->total -= offset + (double) returned_knode_p->out_degree;
      return returned_knode_p;
    }
    total += (double) treapnode_p->left->total;
  }
  total += (double) treapnode_p->count * (treapnode_p->offset + (double) treapnode_p->value);
  if(uniform_sample < total / bstreap_p->total) {
    returned_knode_p = treapnode_p->knode_p;
    treapnode_p->count--;
    if (in)
      treapnode_p->total -= offset + (double) returned_knode_p->in_degree;
    else
      treapnode_p->total -= offset + (double) returned_knode_p->out_degree;
    return returned_knode_p;
  }
  if(treapnode_p->right != NULL) {
    returned_knode_p = bstreap_sample_destructive_helper(bstreap_p, treapnode_p->right, total, uniform_sample, offset, in);
    if (in) 
      treapnode_p->total -= offset + (double) returned_knode_p->in_degree;
    else
      treapnode_p->total -= offset + (double) returned_knode_p->out_degree;
    return returned_knode_p;
  }
  return NULL; //should not happen!
}


			 
void padding(char ch, int n) {
  int i;

  for(i=0; i<n; i++)
    putchar(ch);
}

void structure(treapnode* treapnode_p, int level) {
  int i;

  if(treapnode_p == NULL) {
    padding('\t', level);
    puts("~");
  }
  else {
    structure(treapnode_p->right, level + 1);
    padding('\t', level);
    printf("%d\n", treapnode_p->value);
    structure(treapnode_p->left, level + 1);
  }
}

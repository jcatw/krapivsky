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
  
  return new_treapnode_p;
}

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
  //printf("Call to bstreap_insert.\n");
  if(bstreap_p->root == NULL) {
    bstreap_p->root = talloc(knode_p, value, offset);    
    bstreap_p->n_items++;
    bstreap_p->total += offset + (double) value;    
  }
  else
    bstreap_insert_help(bstreap_p, bstreap_p->root, knode_p, value, offset, NULL, 0);
  
  if(!heap_property_satisfied(bstreap_p)) {
    fprintf(stderr,"Heap property violated after call to bstreap_insert.\n");
    fprintf(stderr,"Id structure\n");
    //structure_id(bstreap_p->root,0);
    fprintf(stderr,"Total structure\n");
    //structure_total(bstreap_p->root,0);
  }
  if(!total_property_satisfied(bstreap_p)) {
    fprintf(stderr,"Total property violated after call to bstreap_insert.\n");
    fprintf(stderr,"Id structure\n");
    //structure_id(bstreap_p->root,0);
    fprintf(stderr,"Total structure\n");
    //structure_total(bstreap_p->root,0);
  }
}

void bstreap_insert_help(bstreap* bstreap_p, treapnode *treapnode_p, knode *knode_p, int value, double offset, treapnode *parent, int left) {
  treapnode_p->total += offset + (double) value;
  
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
    return treapnode_p->knode_p;
  if(treapnode_p->right != NULL)
    return bstreap_sample_helper(bstreap_p, treapnode_p->right, total, uniform_sample);
  return NULL; //should not happen!
}

knode* bstreap_sample_destructive(bstreap *bstreap_p, double offset, int in) {
  knode *returned_knode_p;
  double uniform_sample = rand() / (double)RAND_MAX;

  //printf("Call to bstreap_sample_destructive\n");
  
  bstreap_p->n_items--;
  returned_knode_p = bstreap_sample_destructive_helper(bstreap_p, bstreap_p->root, NULL, 0.0, uniform_sample, offset, in, 0);
  if (in)
    bstreap_p->total -= offset + (double) returned_knode_p->in_degree;
  else
    bstreap_p->total -= offset + (double) returned_knode_p->out_degree;
  if(!heap_property_satisfied(bstreap_p)) {
    fprintf(stderr,"Heap property violated after call to bstreap_sample_destructive.\n");
    fprintf(stderr,"In: %d.\n",in);
    fprintf(stderr,"Id structure\n");
    //structure_id(bstreap_p->root,0);
    fprintf(stderr,"Total structure\n");
    //structure_total(bstreap_p->root,0);
  }
  if(!total_property_satisfied(bstreap_p)) {
    fprintf(stderr,"Total property violated after call to bstreap_sample_destructive.\n");
    fprintf(stderr,"In: %d.\n",in);
    fprintf(stderr,"Id structure\n");
    //structure_id(bstreap_p->root,0);
    fprintf(stderr,"Total structure\n");
    //structure_total(bstreap_p->root,0);
  }
  return returned_knode_p;
}

knode* bstreap_sample_destructive_helper(bstreap *bstreap_p, treapnode *treapnode_p, treapnode *parent_p, double total, double uniform_sample, double offset, int in, int left) {
  knode *returned_knode_p;

  // check left
  if(treapnode_p->left != NULL) {
    if(uniform_sample < (total + ((double) treapnode_p->left->total)) / bstreap_p->total) {
      returned_knode_p = bstreap_sample_destructive_helper(bstreap_p, treapnode_p->left, treapnode_p, total, uniform_sample, offset, in, 1);
      if (in)
	treapnode_p->total -= offset + (double) returned_knode_p->in_degree;
      else
	treapnode_p->total -= offset + (double) returned_knode_p->out_degree;
      return returned_knode_p;
    }
    total += (double) treapnode_p->left->total;
  }

  // check center
  total += (double) treapnode_p->count * (treapnode_p->offset + (double) treapnode_p->value);
  if(uniform_sample < total / bstreap_p->total) {
    returned_knode_p = treapnode_p->knode_p;
    treapnode_p->count--;
    if (in)
      treapnode_p->total -= offset + (double) returned_knode_p->in_degree;
    else
      treapnode_p->total -= offset + (double) returned_knode_p->out_degree;

    // clean up
    if(treapnode_p->count == 0)
      bstreap_delete_node(bstreap_p, treapnode_p, parent_p, left);
    
    return returned_knode_p;
  }

  // check right
  if(treapnode_p->right != NULL) {
    returned_knode_p = bstreap_sample_destructive_helper(bstreap_p, treapnode_p->right, treapnode_p, total, uniform_sample, offset, in, 0);
    if (in) 
      treapnode_p->total -= offset + (double) returned_knode_p->in_degree;
    else
      treapnode_p->total -= offset + (double) returned_knode_p->out_degree;
    return returned_knode_p;
  }
  fprintf(stderr,"Failed to sample a node.\n");
  return NULL; //should not happen!
}

// this function adapted from 'remove' at
// http://opendatastructures.org/ods-java/7_2_Treap_Randomized_Binary.html
void bstreap_delete_node(bstreap *bstreap_p, treapnode *treapnode_p, treapnode *parent_p, int left) {
  treapnode *initial_treapnode_p = treapnode_p;
  treapnode *initial_parent_p = parent_p;
  int i = 0;

  //if(parent_p != NULL)
    //printf("Removing treapnode %d with parent %d.\n",
    //treapnode_p->knode_p->id,
    //  parent_p->knode_p->id);
  //else
    //printf("Removing treapnode %d at root.\n",
  //treapnode_p->knode_p->id);

  
  //if (parent_p != NULL) {
  //    if (treapnode_p->value <= parent_p->value)
  //	left = 1;
  //    else
  //	left = 0;
  //}
  while(treapnode_p->left != NULL || treapnode_p->right != NULL) {
    i++;
    if (treapnode_p != initial_treapnode_p)
      fprintf(stderr,"Deleted wrong node!");
    //if (i > 200)
      //printf("Whoahthere.");
    if(treapnode_p->left == NULL) {
      //printf("leftnull\n");
      //printf("rotating left about %d.\n",treapnode_p->knode_p->id);
      //printf("before:\n");
      //structure_id(bstreap_p->root,0);
      rotate_left(&treapnode_p);
      
      if (parent_p != NULL) {
	if (left)
	  parent_p->left = treapnode_p;
	else
	  parent_p->right = treapnode_p;
      }
      else
	bstreap_p->root = treapnode_p;
      //printf("after:\n");
      //structure_id(bstreap_p->root,0);
      parent_p = treapnode_p;
      treapnode_p = treapnode_p->left;
      left = 1;
    }
    else if (treapnode_p->right == NULL) {
      //printf("rightnull\n");
      //printf("rotating right about %d.\n",treapnode_p->knode_p->id);
      //printf("before:\n");
      //structure_id(bstreap_p->root,0);
      rotate_right(&treapnode_p);
      
      if(parent_p != NULL) {
	if (left)
	  parent_p->left = treapnode_p;
	else
	  parent_p->right = treapnode_p;
      }
      else
	bstreap_p->root = treapnode_p;
      //printf("after:\n");
      //structure_id(bstreap_p->root,0);
      parent_p = treapnode_p;
      treapnode_p = treapnode_p->right;
      left = 0;
    }
    else if (treapnode_p->left->priority > treapnode_p->right->priority) {
      //printf("leftlessright\n");
      //printf("rotating right about %d.\n",treapnode_p->knode_p->id);
      //printf("before:\n");
      //structure_id(bstreap_p->root,0);
      rotate_right(&treapnode_p);
      
      if(parent_p != NULL) {
	if (left)
	  parent_p->left = treapnode_p;
	else
	  parent_p->right = treapnode_p;
      }
      else
	bstreap_p->root = treapnode_p;
      //printf("after:\n");
      //structure_id(bstreap_p->root,0);
      parent_p = treapnode_p;
      treapnode_p = treapnode_p->right;
      left = 0;
    }
    else {
      //printf("else\n");
      //printf("rotating left about %d.\n",treapnode_p->knode_p->id);
      //printf("before:\n");
      //structure_id(bstreap_p->root,0);
      rotate_left(&treapnode_p);
      
      if(parent_p != NULL) {
	if (left)
	  parent_p->left = treapnode_p;
	else
	  parent_p->right = treapnode_p;
      }
      else
	bstreap_p->root = treapnode_p;
      //printf("after:\n");
      //structure_id(bstreap_p->root,0);
      parent_p = treapnode_p;
      treapnode_p = treapnode_p->left;
      left = 1;
    }
  }
  // if root, set treap root to NULL
  if (bstreap_p->root == treapnode_p)
    bstreap_p->root = NULL;
  // if left, set parent left to NULL
  //else if (treapnode_p->value <= parent_p->value)
  else if (left) {
    parent_p->left = NULL;
    //initial_parent_p->total -= (float) treapnode_p->value + treapnode_p->offset;
  }
  // if right, set parent right to NULL
  else {
    parent_p->right = NULL;
    //initial_parent_p->total -= (float) treapnode_p->value + treapnode_p->offset;
  }
  free(treapnode_p);
}

int heap_property_satisfied(bstreap *bstreap_p) {
  return heap_property_satisfied_helper(bstreap_p->root);
}

int heap_property_satisfied_helper(treapnode *treapnode_p) {
  if(treapnode_p == NULL)
    return 1;
  return (int) (heap_property_satisfied_helper(treapnode_p->left) &&
		(treapnode_p->left == NULL || treapnode_p->priority > treapnode_p->left->priority) &&
		(treapnode_p->right == NULL || treapnode_p->priority > treapnode_p->right->priority) &&
		heap_property_satisfied_helper(treapnode_p->right));
}

int total_property_satisfied(bstreap *bstreap_p) {
  return total_property_satisfied_helper(bstreap_p->root);
}

int total_property_satisfied_helper(treapnode *treapnode_p) {
  float left_total;
  float right_total;

  if(treapnode_p == NULL)
    return 1;

  if(treapnode_p->left == NULL)
    left_total = 0.;
  else
    left_total = treapnode_p->left->total;

  if(treapnode_p->right == NULL)
    right_total = 0.;
  else
    right_total = treapnode_p->right->total;
    
  return (int) (total_property_satisfied_helper(treapnode_p->left) &&
		(treapnode_p->total - (float) treapnode_p->count * ((float) treapnode_p->value + treapnode_p->offset) - (left_total + right_total) < FLT_TOLERANCE) &&
		total_property_satisfied_helper(treapnode_p->right));
}
  
void padding(char ch, int n) {
  int i;

  for(i=0; i<n; i++)
    putchar(ch);
}

void structure(treapnode *treapnode_p, int level) {
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

void structure_total(treapnode *treapnode_p, int level) {
  int i;

  if(treapnode_p == NULL) {
    padding('\t', level);
    puts("~");
  }
  else {
    structure_total(treapnode_p->right, level + 1);
    padding('\t', level);
    printf("%g:%g\n",
	   treapnode_p->total,
	   treapnode_p->total - treapnode_p->count*(treapnode_p->value + treapnode_p->offset));
    structure_total(treapnode_p->left, level + 1);
  }
}

void structure_id(treapnode *treapnode_p, int level) {
  int i;

  if(treapnode_p == NULL) {
    padding('\t', level);
    puts("~");
  }
  else {
    structure_id(treapnode_p->right, level + 1);
    padding('\t', level);
    printf("%d\n",treapnode_p->knode_p->id);
    structure_id(treapnode_p->left, level + 1);
  }
}

#include <stdlib.h>

typedef struct knode_temp {
  int in_degree;
  int out_degree;
} knode;

typedef struct knode_list_temp {
  knode *knode_p;
  struct knode_list_temp *next;
} knode_list;

typedef struct treapnode_temp {
  int value;
  int priority;
  int count;
  double total;
  double offset;
  struct treapnode_temp *left;
  struct treapnode_temp *right;
  knode_list *knode_list_p;
} treapnode;

typedef struct {
  int n_items;
  double total;
  treapnode* root;
} bstreap;

knode* kalloc(int, int);

bstreap* bstreap_new();

treapnode* talloc(knode*,int, double);
knode* sample_knode(treapnode*);
knode* remove_random_knode(treapnode*);

void rotate_left(treapnode**);
void rotate_right(treapnode**);
void bstreap_insert(bstreap*, knode*, int, double);
void bstreap_insert_help(bstreap*,treapnode*,knode*,int,double,treapnode*,int);
knode* bstreap_decrement(bstreap*, int, double);
knode* bstreap_decrement_helper(treapnode*, int, double);
knode* bstreap_sample(bstreap*);
knode* bstreap_sample_helper(bstreap*, treapnode*, double, double);
knode* bstreap_sample_destructive(bstreap*,double,int);
knode* bstreap_sample_destructive_helper(bstreap*, treapnode*, double, double, double,int);

void padding(char, int);
void structure(treapnode*, int);

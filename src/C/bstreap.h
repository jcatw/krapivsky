#include <stdlib.h>

typedef struct knode_temp knode;
typedef struct knode_list_temp knode_list;


struct knode_temp {
  int id;
  int in_degree;
  int out_degree;
  knode_list *adjacency_list;
};

struct knode_list_temp {
  knode *knode_p;
  knode_list *next;
};


typedef struct treapnode_temp {
  int value;
  int priority;
  int count;
  double total;
  double offset;
  knode *knode_p;
  struct treapnode_temp *left;
  struct treapnode_temp *right;
} treapnode;

typedef struct {
  int n_items;
  double total;
  treapnode* root;
} bstreap;

knode* kalloc(int, int, int);

void extend_knode_list(knode*, knode*);

bstreap* bstreap_new();

treapnode* talloc(knode*,int, double);
//knode* sample_knode(treapnode*);
//knode* remove_random_knode(treapnode*);

void rotate_left(treapnode**);
void rotate_right(treapnode**);
void bstreap_insert(bstreap*, knode*, int, double);
void bstreap_insert_help(bstreap*,treapnode*,knode*,int,double,treapnode*,int);
//knode* bstreap_decrement(bstreap*, int, double);
//knode* bstreap_decrement_helper(treapnode*, int, double);
knode* bstreap_sample(bstreap*);
knode* bstreap_sample_helper(bstreap*, treapnode*, double, double);
knode* bstreap_sample_destructive(bstreap*,double,int);
knode* bstreap_sample_destructive_helper(bstreap*, treapnode*, double, double, double,int);

void padding(char, int);
void structure(treapnode*, int);

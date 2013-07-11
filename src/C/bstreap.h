#include <stdlib.h>

#define FLT_TOLERANCE 0.005

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
void add_adjacent_node(knode*, knode*);

bstreap* bstreap_new();

treapnode* talloc(knode*,int, double);

void rotate_left(treapnode**);
void rotate_right(treapnode**);
void bstreap_insert(bstreap*, knode*, int, double);
void bstreap_insert_help(bstreap*,treapnode*,knode*,int,double,treapnode*,int);
knode* bstreap_sample(bstreap*);
knode* bstreap_sample_helper(bstreap*, treapnode*, double, double);
knode* bstreap_sample_destructive(bstreap*,double,int);
knode* bstreap_sample_destructive_helper(bstreap*, treapnode*, treapnode*, double, double, double, int, int);
void bstreap_delete_node(bstreap*, treapnode*, treapnode*, int);

int heap_property_satisfied(bstreap*);
int heap_property_satisfied_helper(treapnode*);
int total_property_satisfied(bstreap*);
int total_property_satisfied_helper(treapnode*);

void padding(char, int);
void structure(treapnode*, int);
void structure_total(treapnode*, int);
void structure_id(treapnode*, int);

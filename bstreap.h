#include <stdlib.h>

typedef struct treapnode_temp {
  int value;
  int priority;
  int count;
  double total;
  double offset;
  struct treapnode_temp *left;
  struct treapnode_temp *right;
} treapnode;

typedef struct {
  int n_items;
  double total;
  treapnode* root;
} bstreap;


bstreap* bstreap_new();

treapnode* talloc(int, double);

void rotate_left(treapnode**);
void rotate_right(treapnode**);
void bstreap_insert(bstreap*, int, double);
void bstreap_insert_help(bstreap*,treapnode*,int,double,treapnode*,int);
void bstreap_decrement(bstreap*, int, double);
void bstreap_decrement_helper(treapnode*, int, double);
int bstreap_sample(bstreap*);
int bstreap_sample_helper(bstreap*, treapnode*, double, double);

void padding(char, int);
void structure(treapnode*, int);

#include "krapivsky.h"

void krapivsky(double p,
	       double lambda,
	       double mu,
	       int target_n_nodes,
	       int n_samples,
	       char *sample_file_name,
	       char *all_file_name,
	       char *node_file_name,
	       char *edge_file_name) {
  int i;
  
  FILE *file;
  FILE *all_file;
  FILE *node_file;
  FILE *edge_file;
  
  bstreap* in_degree = bstreap_new();
  bstreap* out_degree = bstreap_new();
  
  int current_n_nodes = 3;
  
  double uniform_sample = 0.;

  knode *knode_indeg_p, *knode_outdeg_p;
  knode *new_knode_p;
  knode *sampled_knode;
  
  knode_list *adjacency_item;

  knode *knodes[target_n_nodes];

  // initial network:
  // 0 --> 1
  // 0 --> 2
  // 1 --> 2
  //
  // 0  --> 1
  //  \     |
  //   \    v
  //    --> 2
  knodes[0] = kalloc(0,0,2);
  knodes[1] = kalloc(1,1,1);
  knodes[2] = kalloc(2,2,0);

  add_adjacent_node(knodes[0],knodes[1]);
  add_adjacent_node(knodes[0],knodes[2]);
  add_adjacent_node(knodes[1],knodes[2]);
  
  bstreap_insert(out_degree, knodes[0], 2, mu);
  bstreap_insert(in_degree, knodes[0], 0, lambda);

  bstreap_insert(out_degree, knodes[1], 1, mu);
  bstreap_insert(in_degree, knodes[1], 1, lambda);

  bstreap_insert(out_degree, knodes[2], 0, mu);
  bstreap_insert(in_degree, knodes[2], 2, lambda);


  printf("Simulating Krapivsky model with %d nodes\n", target_n_nodes);
  while (current_n_nodes < target_n_nodes) {
    //if (current_n_nodes % 1000 == 0)
    //  printf("%d nodes simulated\n", current_n_nodes);
    uniform_sample = rand() / (double)RAND_MAX;
    
    // if we are adding a node
    if (uniform_sample < p) {
      //printf("Step: node addition.\n");
      // destructively sample a new node by in degree, increase degree, then put it back in
      knode_indeg_p = bstreap_sample_destructive(in_degree, lambda, 1);
      knode_indeg_p->in_degree++;
      bstreap_insert(in_degree, knode_indeg_p, knode_indeg_p->in_degree, lambda);
      
      // add a node of out-degree 1, in-degree 0
      new_knode_p = kalloc(current_n_nodes,0,1);
      add_adjacent_node(new_knode_p, knode_indeg_p);
      bstreap_insert(out_degree, new_knode_p, 1, mu);
      bstreap_insert(in_degree, new_knode_p, 0, lambda);

      knodes[current_n_nodes] = new_knode_p;
      
      // increment the current number of nodes
      current_n_nodes++;
    }
    else {// if we are adding an edge
      //printf("Step: edge addition.\n");
      // destructively sample the tail of the new edge, increment out degree, then re-insert
      knode_outdeg_p = bstreap_sample_destructive(out_degree, mu, 0);
      knode_outdeg_p->out_degree++;
      bstreap_insert(out_degree, knode_outdeg_p, knode_outdeg_p->out_degree, mu);

      // destructively sample the head of the new edge, increment in degree, then re-insert
      knode_indeg_p = bstreap_sample_destructive(in_degree, lambda, 1);
      knode_indeg_p->in_degree++;
      bstreap_insert(in_degree, knode_indeg_p, knode_indeg_p->in_degree, lambda);

      add_adjacent_node(knode_outdeg_p, knode_indeg_p);
    }
    //printf("in-degree treap:\n");
    //printf("id:\n");
    //structure_id(in_degree->root,0);
    //printf("total:\n");
    //structure_total(in_degree->root,0);
    //
    //printf("out-degree treap:\n");
    //printf("id:\n");
    //structure_id(out_degree->root,0);
    //printf("total:\n");
    //structure_total(out_degree->root,0);
  }
  printf("Simulation complete.\n");


  printf("Sampling %d nodes into %s\n", n_samples, sample_file_name);

  file = fopen(sample_file_name,"w");
  fprintf(file, "out-degree,in-degree\n");
  for(i=0; i<n_samples; i++) {
    sampled_knode = knodes[rand() % target_n_nodes];
    fprintf(file,"%d, %d\n", sampled_knode->out_degree, sampled_knode->in_degree);
    //printf("(%d, %d)\n", sampled_knode->out_degree, sampled_knode->in_degree);
  }
  fclose(file);

  printf("Writing all nodes into %s\n", all_file_name);
  all_file = fopen(all_file_name, "w");
  for(i=0;i<target_n_nodes;i++) {
    fprintf(all_file, "%d,%d\n", knodes[i]->out_degree, knodes[i]->in_degree);
  }
  fclose(all_file);

  printf("Writing network nodes and edges to %s and %s\n", node_file_name, edge_file_name);
  node_file = fopen(node_file_name, "w");
  edge_file = fopen(edge_file_name, "w");
  for(i=0; i<target_n_nodes; i++) {
    fprintf(node_file,"%d\n",knodes[i]->id);

    adjacency_item = knodes[i]->adjacency_list;
    while(adjacency_item != NULL) {
      fprintf(edge_file,
	      "%d,%d\n",
	      knodes[i]->id,
	      adjacency_item->knode_p->id);
      adjacency_item = adjacency_item->next;
    }
  }
  fclose(node_file);
  fclose(edge_file);
}

void usage() {
  printf("Usage:\nkrapivsky p lambda mu target_n_nodes n_samples sample_output_filename.csv all_output_filename.csv node_output_filename.csv edge_output_filename.csv\n");
}

int main(int argc, char** argv) {
  if (argc != 10) {
    usage();
    return -1;
  }
  double p, lambda, mu;
  int target_n_nodes, n_samples;

  srand ( (unsigned)time ( NULL ) );
  
  sscanf(argv[1], "%lf", &p);
  sscanf(argv[2], "%lf", &lambda);
  sscanf(argv[3], "%lf", &mu);
  sscanf(argv[4], "%d", &target_n_nodes);
  sscanf(argv[5], "%d", &n_samples);
  
  krapivsky(p,
	    lambda,
	    mu,
	    target_n_nodes,
	    n_samples,
	    argv[6],
	    argv[7],
	    argv[8],
	    argv[9]);
  return 0;
}
	    

  

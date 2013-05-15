#include <stdio.h>
#include <stdlib.h>

#include "krapivsky.h"

void krapivsky(bstreap* in_degree,
	       bstreap* out_degree,
	       double p,
	       double lambda,
	       double mu,
	       int target_n_nodes,
	       int n_samples) {
  int i;
  int current_n_nodes = 0;
  double uniform_sample = 0.;

  int edge_to_in_degree, edge_tail, edge_head;
  int in_degree_sample, out_degree_sample;

  printf("Simulating Krapivsky model with %d nodes\n", target_n_nodes);
  while (current_n_nodes < target_n_nodes) {
    //if (current_n_nodes % 1000 == 0)
    //  printf("%d nodes simulated\n", current_n_nodes);
    uniform_sample = rand() / (double)RAND_MAX;
    
    // if we are adding a node
    if (uniform_sample < p) {
      // sample a new node by in degree
      edge_to_in_degree = bstreap_sample(in_degree);
      
      // increase the in-degree of that node
      bstreap_insert(in_degree, edge_to_in_degree+1, lambda);
      bstreap_decrement(in_degree, edge_to_in_degree, lambda);
      
      // add a node of out-degree 1, in-degree 0
      bstreap_insert(out_degree, 1, mu);
      bstreap_insert(in_degree, 0, lambda);
      
      // increment the current number of nodes
      current_n_nodes++;
    }
    else {// if we are adding an edge
      // sample the tail and head of the edge
      edge_tail = bstreap_sample(out_degree);
      edge_head = bstreap_sample(in_degree);
      
      //increase the approporiate in and out degrees
      bstreap_insert(out_degree, edge_tail+1, mu);
      bstreap_decrement(out_degree, edge_tail, mu);
      
      bstreap_insert(in_degree, edge_head+1, lambda);
      bstreap_decrement(in_degree, edge_head, lambda);
    }
  }
  printf("Simulation complete.\n");
  printf("Sampling %d nodes (out-degree, in-degree)\n", n_samples);
  for(i=0; i<n_samples; i++) {
    out_degree_sample = bstreap_sample(out_degree);
    in_degree_sample = bstreap_sample(in_degree);
    printf("(%d, %d)\n", out_degree_sample, in_degree_sample);
  }
}

void usage() {
  printf("Usage:\nkrapivsky p lambda mu target_n_nodes n_samples\n");
}

int main(int argc, char** argv) {
  if (argc != 6) {
    usage();
    return -1;
  }
  double p, lambda, mu;
  int target_n_nodes, n_samples;
  bstreap* in_degree = bstreap_new();
  bstreap* out_degree = bstreap_new();
  
  sscanf(argv[1], "%lf", &p);
  sscanf(argv[2], "%lf", &lambda);
  sscanf(argv[3], "%lf", &mu);
  sscanf(argv[4], "%d", &target_n_nodes);
  sscanf(argv[5], "%d", &n_samples);
  

  bstreap_insert(out_degree, 2, mu);
  bstreap_insert(in_degree, 0, lambda);

  bstreap_insert(out_degree, 1, mu);
  bstreap_insert(in_degree, 1, lambda);

  bstreap_insert(out_degree, 0, mu);
  bstreap_insert(in_degree, 2, lambda);

  krapivsky(in_degree,
	    out_degree,
	    p,
	    lambda,
	    mu,
	    target_n_nodes,
	    n_samples);
  return 0;
}
	    

  

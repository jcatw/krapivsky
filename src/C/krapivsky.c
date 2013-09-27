#include "krapivsky.h"

void krapivsky(double p,
	       double lambda,
	       double mu,
	       int target_n_nodes,
	       int n_samples,
	       char *sample_file_name,
	       char *all_file_name,
	       char *node_file_name,
	       char *edge_file_name,
	       int variable_fitness) {
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

  // parameters for the random sampler
  int kn[128];
  float fn[128];
  float wn[128];
  unsigned long int jsr = time ( NULL );
  r4_nor_setup(kn,fn,wn);

  // initial network:
  // 0 --> 1
  // 0 --> 2
  // 1 --> 2
  //
  // 0  --> 1
  //  \     |
  //   \    v
  //    --> 2
  if(variable_fitness) {
    knodes[0] = kalloc(0,0,2,
		       (double) exp(lambda + (double) r4_nor(&jsr, kn, fn, wn)),
		       (double) exp(mu + (double) r4_nor(&jsr, kn, fn, wn)));
    knodes[1] = kalloc(1,1,1,
		       (double) exp(lambda + (double) r4_nor(&jsr, kn, fn, wn)),
		       (double) exp(mu + (double) r4_nor(&jsr, kn, fn, wn)));
    knodes[2] = kalloc(2,2,0,
		       (double) exp(lambda + (double) r4_nor(&jsr, kn, fn, wn)),
		       (double) exp(mu + (double) r4_nor(&jsr, kn, fn, wn)));
  }
  else {
    knodes[0] = kalloc(0,0,2,lambda,mu);
    knodes[1] = kalloc(1,1,1,lambda,mu);
    knodes[2] = kalloc(2,2,0,lambda,mu);
  }

  add_adjacent_node(knodes[0],knodes[1]);
  add_adjacent_node(knodes[0],knodes[2]);
  add_adjacent_node(knodes[1],knodes[2]);
  
  bstreap_insert(out_degree, knodes[0], 2, knodes[0]->mu);
  bstreap_insert(in_degree, knodes[0], 0, knodes[0]->lambda);

  bstreap_insert(out_degree, knodes[1], 1, knodes[1]->mu);
  bstreap_insert(in_degree, knodes[1], 1, knodes[1]->lambda);

  bstreap_insert(out_degree, knodes[2], 0, knodes[2]->mu);
  bstreap_insert(in_degree, knodes[2], 2, knodes[2]->lambda);


  printf("Simulating Krapivsky model with %d nodes\n", target_n_nodes);
  while (current_n_nodes < target_n_nodes) {
    //if (current_n_nodes % 1000 == 0)
    //  printf("%d nodes simulated\n", current_n_nodes);
    uniform_sample = rand() / (double)RAND_MAX;
    
    // if we are adding a node
    if (uniform_sample < p) {
      //printf("Step: node addition.\n");
      // destructively sample a new node by in degree, increase degree, then put it back in
      knode_indeg_p = bstreap_sample_destructive(in_degree, 1);
      knode_indeg_p->in_degree++;
      bstreap_insert(in_degree, knode_indeg_p, knode_indeg_p->in_degree, knode_indeg_p->lambda);
      
      // add a node of out-degree 1, in-degree 0
      if( variable_fitness )
	new_knode_p = kalloc(current_n_nodes,0,1,
			     (double) exp(lambda + (double) r4_nor(&jsr, kn, fn, wn)),
			     (double) exp(mu + (double) r4_nor(&jsr, kn, fn, wn)));
      else
	new_knode_p = kalloc(current_n_nodes,0,1,lambda,mu);
      
      add_adjacent_node(new_knode_p, knode_indeg_p);
      bstreap_insert(out_degree, new_knode_p, 1, new_knode_p->mu);
      bstreap_insert(in_degree, new_knode_p, 0, new_knode_p->lambda);

      knodes[current_n_nodes] = new_knode_p;
      
      // increment the current number of nodes
      current_n_nodes++;
    }
    else {// if we are adding an edge
      //printf("Step: edge addition.\n");
      // destructively sample the tail of the new edge, increment out degree, then re-insert
      knode_outdeg_p = bstreap_sample_destructive(out_degree, 0);
      knode_outdeg_p->out_degree++;
      bstreap_insert(out_degree, knode_outdeg_p, knode_outdeg_p->out_degree, knode_outdeg_p->mu);

      // destructively sample the head of the new edge, increment in degree, then re-insert
      knode_indeg_p = bstreap_sample_destructive(in_degree, 1);
      knode_indeg_p->in_degree++;
      bstreap_insert(in_degree, knode_indeg_p, knode_indeg_p->in_degree, knode_indeg_p->lambda);

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
    fprintf(node_file,"%d,%f,%f\n",knodes[i]->id,knodes[i]->lambda,knodes[i]->mu);

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
  printf("Usage:  krapivsky [options] nnodes\n\n \
\tnnodes: number of nodes to simulate\n\n \
\toptions:\n \
\t--------\n \
\t\t--p:\t\tmodel parameter p, the probability of taking a node step.  (default: p=0.5) \n \
\t\t--lambda:\tmodel parameter lambda, the in-degree fitness of nodes.  (default: lambda=0.2)\n \
\t\t--mu:\t\tmodel parameter mu, the out-degree fitness of nodes.  (default: mu=0.2)\n \
\t\t--nsamples:\tnumber of out-degree,in-degree samples to take.  (default: nsamples=100)\n \
\t\t--samplefile:\tfilename for sample out-degree,in-degree output.  (default: samplefile=\"samples.csv\")\n \
\t\t--allfile:\tfilename for all out-degree,in-degree pairs.  (default: allfile=\"allsamples.csv\")\n \
\t\t--nodefile:\tfilename for nodes.  (default: nodefile=\"nodes.csv\")\n \
\t\t--edgefile:\tfilename for edges.  (default: edgefile=\"edges.csv\"\n \
\t\t--variable-fitness: if this flag is present, sample mu and lambda from a standard lognormal with means defined by the mu and lambda parameters.\n \
\n");
}

int main(int argc, char** argv) {
  if (argc < 2) {
    usage();
    return -1;
  }
  int nnodes;

  double p=0.5;
  double lambda=0.2;
  double mu=0.2;
  int nsamples=100;
  char samplefile [ARGLEN] = "samples.csv";
  char allfile    [ARGLEN] = "allsamples.csv";
  char nodefile   [ARGLEN] = "nodes.csv";
  char edgefile   [ARGLEN] = "edges.csv";
  int variable_fitness = 0;

  

  srand ( (unsigned)time ( NULL ) );
  
  while(argc > 1 && argv[1][0] == '-' && argv[1][1] == '-') {  //only permits --arguments (no -arguments)
    if( strcmp(&argv[1][2],"p") == 0) {
      sscanf(argv[2], "%lf", &p);
      argc-=2;
      argv+=2;
    }
    else if ( strcmp(&argv[1][2],"lambda") == 0 ) {
      sscanf(argv[2], "%lf", &lambda);
      argc-=2;
      argv+=2;
    }
    else if ( strcmp(&argv[1][2],"mu") == 0) {
      sscanf(argv[2], "%lf", &mu);
      argc-=2;
      argv+=2;
    }
    else if ( strcmp(&argv[1][2],"nsamples") == 0) {
      sscanf(argv[2], "%d", &nsamples);
      argc-=2;
      argv+=2;
    }
    else if ( strcmp(&argv[1][2],"samplefile") == 0 ) {
      strcpy(samplefile,argv[2]);
      argc-=2;
      argv+=2;
    }
    else if ( strcmp(&argv[1][2],"allfile") == 0) {
      strcpy(allfile,argv[2]);
      argc-=2;
      argv+=2;
    }
    else if ( strcmp(&argv[1][2],"nodefile") == 0) {
      strcpy(nodefile,argv[2]);
      argc-=2;
      argv+=2;
    }
    else if ( strcmp(&argv[1][2],"edgefile") == 0) {
      strcpy(edgefile,argv[2]);
      argc-=2;
      argv+=2;
    }
    else if ( strcmp(&argv[1][2],"variable-fitness") == 0 ) {
      variable_fitness = 1;
      argc--;
      argv++;
    }
  }
  if(argc != 2) {
    usage();
    return -1;
  }
  sscanf(argv[1], "%d", &nnodes);

  krapivsky(p,
	    lambda,
	    mu,
	    nnodes,
	    nsamples,
	    samplefile,
	    allfile,
	    nodefile,
	    edgefile,
	    variable_fitness);
  return 0;
}
	    

  

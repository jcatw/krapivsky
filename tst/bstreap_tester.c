#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bstreap.h"

int main() {
  srand ( (unsigned)time ( NULL ) );
  
  int samples[8] = {0,0,0,0,0,0,0,0};
  int sample;
  int i,j;
  double offset = 0.05;
  
  bstreap *a_bstreap = bstreap_new();

  bstreap_insert(a_bstreap, 4, offset);
  bstreap_insert(a_bstreap, 5, offset);
  bstreap_insert(a_bstreap, 3, offset);
  bstreap_insert(a_bstreap, 1, offset);
  bstreap_insert(a_bstreap, 2, offset);
  bstreap_insert(a_bstreap, 3, offset);
  bstreap_insert(a_bstreap, 3, offset);
  bstreap_insert(a_bstreap, 4, offset);
  bstreap_insert(a_bstreap, 2, offset);
  bstreap_insert(a_bstreap, 6, offset);
  bstreap_insert(a_bstreap, 7, offset);
  bstreap_insert(a_bstreap, 1, offset);
  bstreap_insert(a_bstreap, 8, offset);

  structure(a_bstreap->root,0);

  for(i=1; i<=1000; i++) {
    sample = bstreap_sample(a_bstreap);
    samples[sample-1]++;
    printf("sample %d: %d\n", i, sample);
  }

  printf("\n\n");
  for(i=0; i<8; i++) {
    printf("%d :",i+1);
    for(j=0; j<samples[i]/10; j++)
      printf("*");
    printf("\n");
  }
  printf("\n");

  structure(a_bstreap->root,0);
  
  return 0;
}

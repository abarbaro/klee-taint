// RUN: %llvmgcc %s -emit-llvm -g -O0 -c -o %t.bc
// RUN: rm -rf %t.klee-out
// RUN: %klee -taint=direct --output-dir=%t.klee-out -exit-on-error %t.bc



#include<klee/klee.h>
int 
main (int argc, char *argv[])
{
  int a = 1;
  int b = 100;
  int c = 0;
  klee_set_taint (1, &a, sizeof (a));
  klee_set_taint (2, &b, sizeof (b));
  int *ptr = (int *) malloc(2 * sizeof (int));
  *ptr = a;
  *(ptr+1) = b;
  c = *ptr + *(ptr+1);
  klee_assert (klee_get_taint (&c, sizeof (c)) == 1|2 );

  free(ptr);
}


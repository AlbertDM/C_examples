#include <stdio.h>

#define MAX_ARR 7

typedef struct str{
  int *arr[MAX_ARR];
  double value;
}str;

void main() {
  int *p, *q;
  int i_arr[] = {0,1,2,3,4,5,6};
  p = &i_arr[0];  // first element
  q = &i_arr[MAX_ARR];  // last element
  printf("\nNumber of elements in int array = %ld", q - p);

  str str_arr[] = {0};
  str *m, *n;
  m = &str_arr[0];  // first element
  n = &str_arr[MAX_ARR];  // last element
  printf("\nNumber of elements in struct array = %ld", n - m);

  printf("\n");

  return;
}

/* In C there is no real "pass-by-reference" but actually pass-address-by-value
* */

#include <stdio.h>

void swap_integers(int *a, int *b) {
  if (a == NULL && b == NULL) {
    // Handle the null case (e.g., print an error message)
    return;
  }
  // Safe to use *a and *b here

  int temp = *a;
  a = b;  // *a = *b;
  *b = temp;
}

int main() {
  int x = 5, y = 10;
  printf("Before swap: x = %d, y = %d\n", x, y);
  swap_integers(&x, &y);
  printf("After swap: x = %d, y = %d\n", x, y);
  return 0;
}

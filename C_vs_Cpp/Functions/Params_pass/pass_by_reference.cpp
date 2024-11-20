#include <iostream>

using std::cout;  // Better than using namespace std

void swap_integers(int &a, int &b) {
  int temp = a;
  a = b;
  b = temp;
}

int main() {
  int x = 5, y = 10;
  cout << "Before swap: x = " << x << ", y = " << y << std::endl;
  swap_integers(x, y);
  cout << "After swap: x = " << x << ", y = " << y << std::endl;
  return 0;
}

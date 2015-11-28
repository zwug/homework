#include <iostream>

int main() {
  long int value1, value2;
  value1 = 200000;
  long int *LPtr = &value1;
  std::cout << value1 << " | pointer to value1 = " << LPtr << std::endl;
  value2 = *LPtr;
  std::cout << value2 << " | pointer to value2 = " << LPtr << " | address of value1 = " << &value1 <<std::endl;
}

#include <iostream>

int integerPower(int base, int exponent) {
  if (exponent == 1) {
    return base;
  }
  return base * integerPower(base, exponent - 1);
}

int main() {
  int base, exponent;

  while(true) {
    std::cout << "Base value: (typing not numbers will be recognized as quitting)" << std::endl;
    if(std::cin >> base) {
      std::cout << "Exponent value:" << std::endl;
      std::cin >> exponent;
      std::cout << "Result value:" << std::endl;
      std::cout << integerPower(base, exponent) << std::endl;
      std::cout << "**********************" << std::endl << std::endl;
    } else {
      std::cout << "Incorrect base value, quitting..." << std::endl << std::endl;
      break;
    }
  }
}

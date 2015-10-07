#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iomanip>

int intToBin(int number) {
  std::string binary = "";
  int decimal = number;

  while (decimal > 0) {
    int remainder = decimal % 2;
    std::stringstream ss;
    ss << remainder;
    std::string strRemainder = ss.str();
    binary += strRemainder;
    decimal = decimal / 2;
  }

  std::reverse(binary.begin(), binary.end());
  std::cout << std::setw(10) << binary << " = " << number << std::endl;
}

int main () {
  for (int i = 5; i < 513; i++) {
    intToBin(i);
  }
}

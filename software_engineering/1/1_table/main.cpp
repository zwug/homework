#include <iostream>

int integerPower(int base, int exponent) {
  if (exponent == 0) {
    return 1;
  }
  if (exponent == 1) {
    return base;
  }
  return base * integerPower(base, exponent - 1);
}

int binToInt(int binary) {
  // Понижаем порядок числа (левая часть)
  int leftPart = binary / 10;
  // Отделяем низжий разряд в правую часть.
  int rightPart = binary % 10;
  int result = 0;
  for(int i = 0; leftPart > 0 || rightPart > 0; i++) {
    if (rightPart == 1) {
      result += integerPower(2, i);
    }
    rightPart = leftPart % 10;
    leftPart = leftPart / 10;
  }
  return result;
}

int binaryIncrement(int binary) {
  if (binary % 10 == 0) {
    return ++binary;
  }
  return binaryIncrement(binary / 10) * 10;
}

int main () {
  for (int i = 101; i < 1000000000; i = binaryIncrement(i)) {
    std::cout << i << " = " << binToInt(i) << std::endl;
  }
}

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <typeinfo>

int main() {
  char *phone;
  int locale = 0;
  char *string_number;
  long number;

  phone = new char;
  string_number = new char;

  std::cout << "Type the phone..." << std::endl;
  std::cin >> phone;
  std::cout << phone << std::endl;

  char * lexem = strtok(phone, " ()-");

  while (lexem != NULL) {
    if (locale == 0) {
      locale = atoi(lexem);
    } else {
      string_number = strcat(string_number, lexem);
    }

    lexem = strtok (NULL, " ()-");
  }

  number = atoi(string_number);

  std::cout << "Locale index = " << locale << " | typeid = " << typeid(locale).name() << std::endl;
  std::cout << "Number = " << string_number << " | typeid = " << typeid(number).name() << std::endl;
}

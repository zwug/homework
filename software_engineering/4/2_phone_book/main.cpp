#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string.h>

const int NAME_LENGTH = 25;
const int PHONE_LENGTH = 15;
const int ROW_LENGTH = NAME_LENGTH * 2 + PHONE_LENGTH;

void generateName(char* name) {
  const char* letters[2] = { "bcdfghjklmnpqrstvwxyz ", "aeiouy" };
  const char letterlen[2] = { strlen(letters[0]), strlen(letters[1]) };
  for (int i=0; i < NAME_LENGTH; i++) {
    name[i] = letters[i%2][std::rand()%letterlen[i%2]];
  }
  name[0] = toupper(name[0]);
}

void generatePhone(char* number) {
  const char* digits = "1234567890";
  const char digitslen = strlen(digits);
  for (int i=0; i < PHONE_LENGTH - 1; i++) {
    switch (i) {
      case 1:
        number[i] = '(';
        break;
      case 5:
        number[i] = ')';
        break;
      case 9:
        number[i] = '-';
        break;
      default:
        number[i] = digits[std::rand()%digitslen];
        break;
    }
  }
}

void printFile(std::fstream &file) {
  std::cout << std::endl << "***************** Prinitng file ****************" << std::endl << std::endl;
  std::string outputLine;
  file.seekg (0, file.beg);
  getline(file, outputLine);
  std::cout << outputLine << std::endl;
  std::cout << std::endl << "***************** end of file ****************" << std::endl << std::endl;
  std::cout << "Length of the file should be " << ROW_LENGTH * 88 << ", got " << outputLine.length() << std::endl;
  // Проверка форматирования
  bool formatError = false;
  for (int i = 0; i < 88; i++) {
    int offset = i * ROW_LENGTH + 2 * NAME_LENGTH;
    if(outputLine[offset + 1] != '(' || outputLine[offset + 5] != ')' || outputLine[offset + 9] != '-') {
      formatError = true;
      break;
    }
  }
  if(formatError) {
    std::cout << "Correct formatting" << std::endl;
  } else {
    std::cout << "Error: incorrect formatting" << std::endl;
  }
}

int CreateFormatFile(char * filename){
  struct contact {
    char firstName [NAME_LENGTH];
    char lastName [NAME_LENGTH];
    char phone[PHONE_LENGTH];
  };
  std::fstream file;
  file.open(filename, std::ios::binary | std::ios::in | std::ios::out | std::ofstream::trunc);
  if(!file){
    std::cout << "Не удается открыть файл\n";
    return 1;
  }
  // Запись пустых данных
  file.seekg (0, file.beg);
  for (int i = 0; i < 80; i++) {
    contact emptyContact = {"", "", ""};
    file.write((char* ) &emptyContact, sizeof(contact));
  }
  // Запись заполненных данных
  file.seekg (0, file.end);
  for (int i = 0; i < 8; i++) {
    contact testContact;
    generateName(testContact.firstName);
    generateName(testContact.lastName);
    generatePhone(testContact.phone);
    file.write((char* ) &testContact, sizeof(contact));
  }

  printFile(file);
  // Изменение данных
  file.seekg (ROW_LENGTH * 80 + 2 * NAME_LENGTH, file.beg);
  file.write("9(999)999-9999", PHONE_LENGTH);
  file.seekg (ROW_LENGTH * 81, file.beg);
  file.write("Aaron", NAME_LENGTH);
  file.seekg (ROW_LENGTH * 83 + NAME_LENGTH, file.beg);
  file.write("Paul", NAME_LENGTH);
  file.seekg (ROW_LENGTH * 3 + NAME_LENGTH, file.beg);
  file.write("Johnson", NAME_LENGTH);
  printFile(file);
  file.close();
}

int main() {
  char fileName[] = "phone.dat";
  CreateFormatFile(fileName);
}

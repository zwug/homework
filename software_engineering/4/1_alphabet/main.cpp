#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>

int main() {
  std::string fileContent;
  std::vector <char> characters;
  std::ifstream file ("alphabet.txt");
  if (file.is_open()) {
    getline(file, fileContent);
    char *fileLine;
    fileLine = new char [fileContent.length()];
    // Копирование, так как strtok влияет на строку
    strcpy(fileLine, fileContent.c_str());
    char *letter = strtok(fileLine, ",");

    for (int i = 0; letter != NULL; i++) {
      if (*letter == 'p') {
        break;
      } else {
        characters.push_back(*letter);
        if(characters.size() == 11) {
          characters.erase(characters.begin());
        }

      }

      letter = strtok (NULL, ",");
    }
    std::cout << "result array:" << std::endl;
    for (int i = 0; i < characters.size(); i++) {
      std::cout << characters[i] << " ";
    }
    std::cout << "\n";
    file.close();
  }

  else std::cout << "Unable to open file";
  return 0;
}

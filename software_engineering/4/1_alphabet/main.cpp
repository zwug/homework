#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>

const int SYMBOLS_COUNT = 26 * 2; // 25 сиволов, 24 запятые + символ конца строки

int main() {
	char fileContent[SYMBOLS_COUNT];
	std::vector <char> characters;
	std::ifstream file("alphabet.txt");
	if (file.is_open()) {
		file >> fileContent;
		char *next_symbol;
		char *letter = strtok_s(fileContent, ",", &next_symbol);

		for (int i = 0; letter != NULL; i++) {
			if (*letter == 'p') {
				break;
			}
			else {
				characters.push_back(*letter);
				if (characters.size() == 11) {
					characters.erase(characters.begin());
				}
			}

			letter = strtok_s(NULL, ",", &next_symbol);
		}
		std::cout << "result array:" << std::endl;
		for (int i = 0; i < characters.size(); i++) {
			std::cout << characters[i] << " ";
		}
		std::cout << "\n";
		file.close();
	}

	else {
		std::cout << "Unable to open file";
		exit(1);
	}
	std::cin.get();
	return 0;
}

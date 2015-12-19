#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <string.h>

const int NAME_LENGTH = 25;
const int PHONE_LENGTH = 15;
const int ROW_LENGTH = NAME_LENGTH * 2 + PHONE_LENGTH;

void generatePhone(char* number) {
	const char* digits = "1234567890";
	int digitslen = strlen(digits);
	for (int i = 0; i < PHONE_LENGTH - 1; i++) {
		switch (i) {
		case 0:
			number[i] = '8';
			break;
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
			number[i] = digits[std::rand() % digitslen];
			break;
		}
	}
}

void printFile(std::fstream &file, const char filename[]) {
	file.seekg(0, file.end);
	int fileSize = file.tellg();
	char *outputLine;
	outputLine = new char[fileSize + 1];
	std::ifstream fileToRead;
	fileToRead.open(filename, std::ios::binary | std::ios::in);
	if (fileToRead.fail()) {
		std::cout << "Не удается открыть файл\n";
		exit(1);
	}
	fileToRead.seekg(0, fileToRead.beg);
	fileToRead.read(outputLine, file.tellg());
	fileToRead.read(outputLine, file.tellg());
	std::cout << std::endl << "***************** Prinitng file ****************" << std::endl << std::endl;
	for (int i = 0, position = 0; i < fileSize; i++, position++) {
		std::cout << outputLine[i];
		if (position == ROW_LENGTH) {
			position = 0;
		}
		switch (position) {
		case NAME_LENGTH - 1:
		case NAME_LENGTH * 2 - 1:
			std::cout << " | ";
			break;
		case ROW_LENGTH - 1:
			std::cout << "\n";
		default:
			break;
		}
	}
	std::cout << std::endl << "***************** end of file ******************" << std::endl << std::endl;
	std::cout << "Length of the file should be " << ROW_LENGTH * 88 << ", got " << fileSize << std::endl;
	// Проверка форматирования
	bool formatError = false;
	for (int i = 0; i < 88; i++) {
		int offset = i * ROW_LENGTH + 2 * NAME_LENGTH;
		if (outputLine[offset + 1] != '(' || outputLine[offset + 5] != ')' || outputLine[offset + 9] != '-') {
			formatError = true;
			break;
		}
	}
	if (!formatError) {
		std::cout << "Correct formatting" << std::endl;
	}
	else {
		std::cout << "Error: incorrect formatting" << std::endl;
	}
	delete[] outputLine;
	fileToRead.close();
}

int CreateFormatFile(const char filename[]) {
	struct contact {
		char firstName[NAME_LENGTH];
		char lastName[NAME_LENGTH];
		char phone[PHONE_LENGTH];
	};
	std::fstream file;
	file.open(filename, std::ios::binary | std::ios::out | std::ofstream::trunc);
	if (!file) {
		std::cout << "Не удается открыть файл\n";
		return 1;
	}
	// Запись пустых данных
	file.seekg(0, file.beg);
	for (int i = 0; i < 80; i++) {
		contact emptyContact = { "NULL", "NULL", "8(   )   -    " };
		file.write((char*)&emptyContact, sizeof(contact));
	}
	// Запись заполненных данных
	file.seekg(0, file.end);
	for (int i = 0; i < 8; i++) {
		contact testContact = {"Nikolai", "Kurilov", ""};
		generatePhone(testContact.phone);
		file.write((char*)&testContact, sizeof(contact));
	}

	printFile(file, filename);
	// Изменение данных
	char dataToWrite[NAME_LENGTH] = {};
	file.seekg(ROW_LENGTH * 80 + 2 * NAME_LENGTH, file.beg);
	file.write("8(999)999-9999", PHONE_LENGTH);
	file.seekg(ROW_LENGTH * 81, file.beg);
	strcpy_s(dataToWrite, 6, "Aaron");
	file.write(dataToWrite, NAME_LENGTH);
	file.seekg(ROW_LENGTH * 83 + NAME_LENGTH, file.beg);
	strcpy_s(dataToWrite, 5, "Paul");
	file.write(dataToWrite, NAME_LENGTH);
	file.seekg(ROW_LENGTH * 3 + NAME_LENGTH, file.beg);
	strcpy_s(dataToWrite, 8, "Johnson");
	file.write(dataToWrite, NAME_LENGTH);
	
	printFile(file, filename);
	file.close();
}

int main() {
	char fileName[] = "phone.dat";
	CreateFormatFile(fileName);
	std::cin.get();
}

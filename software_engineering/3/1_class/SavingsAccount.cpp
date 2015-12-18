#include <iostream>
#include <iomanip>
#include <string.h>
#include "SavingsAccount.h"

const int BUFFER_SIZE = 25;

SavingsAccount::SavingsAccount(const char name[], const char inputLastName[], double balance) {
	lastName = inputLastName;
	firstName = name;
	SavingsBalance = balance;
};
void SavingsAccount::calculateMonthlyInterest() {
	double monthlyInterest = annualInterestRate * SavingsBalance / 12;
	char fullName[BUFFER_SIZE];
	strcpy_s(fullName, strlen(firstName) + 1, firstName);
	strcat_s(fullName, strlen(firstName) + 2, " ");
	strcat_s(fullName, BUFFER_SIZE, lastName);

	std::cout << std::setw(25) << std::left << "Full Name";
	std::cout << std::setw(25) << std::left << "balance after a month" << "monthly interest" << std::endl;

	std::cout << std::setw(25) << std::left << fullName;
	std::cout << std::setw(25) << std::left << SavingsBalance + monthlyInterest;
	std::cout << monthlyInterest << std::endl << std::endl << std::endl << std::endl;
};
void SavingsAccount::modifyInterestRate(float newRate) {
	annualInterestRate = newRate;
};

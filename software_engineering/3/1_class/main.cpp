#include <iostream>
#include "SavingsAccount.h"

float SavingsAccount::annualInterestRate = 0.0;

int main() {
	SavingsAccount saver1("Sevostianov", "Nikolai", 200000.0);
	SavingsAccount saver2("Emelianov", "Innokentiy", 300000.0);
	SavingsAccount::modifyInterestRate(0.03);
	saver1.calculateMonthlyInterest();
	saver2.calculateMonthlyInterest();
	SavingsAccount::modifyInterestRate(0.04);
	saver1.calculateMonthlyInterest();
	saver2.calculateMonthlyInterest();
	std::cin.get();
	return 0;
}

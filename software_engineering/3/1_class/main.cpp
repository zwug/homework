#include <iostream>
#include <string.h>

class SavingsAccount {
  private:
    char* firstName;
    char* lastName;
    double SavingsBalance;
    static float annualInterestRate;
  public:
    SavingsAccount(char* name, char* inputLastName, double balance) {
      firstName = new char [sizeof(name)];
      strcpy(firstName, name);
      lastName = new char [sizeof(inputLastName)];
      strcpy(lastName, inputLastName);
      SavingsBalance = balance;
    };
    void calculateMonthlyInterest() {
      double monthlyInterest = annualInterestRate * SavingsBalance / 12;
      std::cout << "________________________________________________________" << std::endl << std::endl;
      std::cout << "Balance for " << firstName << " " << lastName << " after a month = ";
      std::cout << SavingsBalance + monthlyInterest << std::endl;
      std::cout << "Calculated monthly interest = " << monthlyInterest << std::endl;
    };
    static void modifyInterestRate(float newRate) {
      annualInterestRate = newRate;
    };
    ~SavingsAccount() {
      delete [] firstName;
      delete [] lastName;
    }
};

float SavingsAccount::annualInterestRate = 0.0;

int main() {
  SavingsAccount saver1((char*)"Sevostianov", (char*)"Nikolai", 200000.0);
  SavingsAccount saver2((char*)"Emelianov", (char*)"Innokentiy", 300000.0);
  SavingsAccount::modifyInterestRate(0.03);
  saver1.calculateMonthlyInterest();
  saver2.calculateMonthlyInterest();
  SavingsAccount::modifyInterestRate(0.04);
  saver1.calculateMonthlyInterest();
  saver2.calculateMonthlyInterest();
  return 0;
}

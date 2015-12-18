class SavingsAccount {
private:
	const char* firstName;
	const char* lastName;
	double SavingsBalance;
	static float annualInterestRate;
public:
	SavingsAccount(const char name[], const char inputLastName[], double balance);
	void calculateMonthlyInterest();
	static void modifyInterestRate(float newRate);
};

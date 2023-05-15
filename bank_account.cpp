#include <iostream>
using namespace std;

class BankAccount {
    private:
        int accountID;
        double balance;

    public:
        BankAccount(int id, double initialBalance) {
            this->accountID = id;
            this->balance = initialBalance;
        }

        int getAccountID() {
            return this->accountID;
        }

        double getBalance() {
            return this->balance;
        }

        void credit (BankAccount bank, double value) {
		    bank->balance = bank->balance + value;
	    }

        void debit (BankAccount bank, double value) {
		    bank->balance = bank->balance - value;
	    }

        void transfer (BankAccount origin, BankAccount destination, double value) {
		    debit(origin, value);
		    credit(destination, value);
	    }
};
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

        void credit (double value) {
		    this->balance = this->balance + value;
	    }

        void debit (double value) {
		    this->balance = this->balance - value;
	    }

        void transfer (BankAccount* destination, double value) {
		    this->debit(value);
		    destination->credit(value);
	    }
};
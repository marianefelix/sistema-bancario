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
};
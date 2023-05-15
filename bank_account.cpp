#include <iostream>
using namespace std;

class BankAccount {
    private:
        int userID;
        double balance;

    public:
        BankAccount();

        BankAccount(int id, double initialBalance) {
            this->userID = id;
            this->balance = initialBalance;
        }

        int getUserID() {
            return this->userID;
        }

        double getBalance() {
            return this->balance;
        }
};
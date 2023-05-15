#include <vector>
#include <iostream>
#include "bank_account.cpp"

using namespace std;

class Bank {
    private:
        vector<BankAccount> accounts;
    
    public:
        // Constructor
        Bank() {}

        // Add an account to the bank
        void addAccount(int accountID) {
            for (BankAccount account : this->accounts) {
                if (account.getAccountID() == accountID) {
                    return "Essa conta já existe.";
                }
            }

            BankAccount newAccount(accountID, 0.0);
            this->accounts.push_back(newAccount);

            return "Conta criada com sucesso!";
        }

        BankAccount getAccountByID(int accountID) {
            for (BankAccount account : this->accounts) {
                if (account.getAccountID() == accountID) {
                    return account;
                }
            }

            BankAccount errorAccount(-1, -1);
            return errorAccount;
        }
};
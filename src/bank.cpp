#include <vector>
#include <iostream>
#include "bank_account.cpp"

class Bank {
    public:
        // Constructor
        Bank() {}

        // Add an account to the bank
        void addAccount() {
            int accountNumber;
            std::cout << "Enter account number: ";
            std::cin >> accountNumber;

            for(BankAccount account : accounts) {
                if(account.getUserID() == accountNumber) {
                    std::cout << "Account already exists." << std::endl;
                    return;
                }
            }

            BankAccount new_account(accountNumber, 0.0);
            accounts.push_back(new_account);

            std::cout << "Account " << accountNumber << " created." << std::endl;
            return;
        }    

    private:
        std::vector<BankAccount> accounts;

};
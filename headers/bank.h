#ifndef BANK_H
#define BANK_H

#include <iostream>
#include <vector>
#include "bank_account.h"
#include "savings_account.h"

class Bank {
    private:
        std::vector<BankAccount*> accounts;

    public:
        Bank(); //constructor
        ~Bank(); //destructor

        std::string addAccount(int accountID, double openingBalance);
        std::string addSavingsAccount(int accountID, double openingBalance);
        std::string addBonusAccount(int accountID);

        BankAccount* getAccountByID(int accountID);
        std::string getAccountType(BankAccount* account);
};

#endif
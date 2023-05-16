#ifndef BANK_H
#define BANK_H

#include <vector>
#include "bank_account.h"

class Bank {
    private:
        std::vector<BankAccount> accounts;
    
    public:
        Bank(); //constructor
        ~Bank(); //destructor

        std::string addAccount(int accountID);

        BankAccount getAccountByID(int accountID);
};

#endif
#ifndef SAVINGS_ACCOUNT_H
#define SAVINGS_ACCOUNT_H

#include "bank_account.h"

class SavingsAccount : public BankAccount { // inherits BankAccount class
    private:
        double interestRate; // additional feature
    
    public:
        SavingsAccount(int id, double initialBalance); // constructor
        ~SavingsAccount(); // destructor

        double getInterestRate() const;

        void applyInterestRate(double value) override;
};

#endif
#ifndef SAVINGS_ACCOUNT_H
#define SAVINGS_ACCOUNT_H

#include "bank_account.h"

class SavingsAccount : public BankAccount { // inherits BankAccount class
    private:
        double interestRate; // additional feature
    
    public:
        SavingsAccount(int id, double initialBalance); // constructor
        virtual ~SavingsAccount(); // destructor

        double getInterestRate() const;

        void applyInterestRate(double value) override;

        void debit(double value) override;

        void transfer(BankAccount& destination, double value) override;

        virtual void addBonusCredit(double value);
        virtual void addBonusTransfer(double value);
};

#endif
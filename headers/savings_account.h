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
<<<<<<< HEAD
        virtual void addBonusCredit(double value);
        virtual void addBonusTransfer(double value);
=======
>>>>>>> 76e138ed006e22f608b7c94acdd2ac8682f722e6
};

#endif
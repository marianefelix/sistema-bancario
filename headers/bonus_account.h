#ifndef BONUS_ACCOUNT_H
#define BONUS_ACCOUNT_H

#include "bank_account.h"

class BonusAccount : public BankAccount {
    private:
        int score;
    
    public:
        BonusAccount(int id, double initialBalance); //constructor
        virtual ~BonusAccount(); //destructor

        double getScore() const;
        
        virtual void applyInterestRate(double value);
        void addBonusCredit(double value) override;
        void addBonusTransfer(double value) override;
};

#endif
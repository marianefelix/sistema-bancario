#ifndef BONUS_ACCOUNT_H
#define BONUS_ACCOUNT_H

class BonusAccount {
    private:
        int score;
    
    public:
        BonusAccount(int id, double initialBalance); //constructor
        ~BonusAccount(); //destructor

        void addBonusCredit(double amount);

        void addBonusTransfer(double amount);

        double getScore() const;
};

#endif
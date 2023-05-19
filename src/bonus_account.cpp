#include <iostream>
#include "../headers/bank_account.h"
using namespace std;

class BonusAccount : public BankAccount {
private:
    int score;

public:
    BonusAccount(int id, double initialBalance) : BankAccount(id, initialBalance), score(10) {}
    ~BonusAccount();

    void addBonusCredit(double amount) {
        int requiredAmount = 100;
        this->score += (static_cast<int>(amount) / requiredAmount);
    }

    void addBonusTransfer(double amount) {
        int requiredAmount = 200;
        this->score += (static_cast<int>(amount) / requiredAmount);
    }

    double getScore() const {
        return this->score;
    }
};
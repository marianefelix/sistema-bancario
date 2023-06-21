#include <iostream>
#include "../headers/bank_account.h"
#include "../headers/bonus_account.h"
using namespace std;

BonusAccount::BonusAccount(int id, double initialBalance) : BankAccount(id, initialBalance), score(10) {}

BonusAccount::~BonusAccount() {}

void BonusAccount::addBonusCredit(double amount) {
    int requiredAmount = 100;
    this->score += (static_cast<int>(amount) / requiredAmount);
}

void BonusAccount::addBonusTransfer(double amount) {
    int requiredAmount = 150;
    this->score += (static_cast<int>(amount) / requiredAmount);
}

double BonusAccount::getScore() const {
    return this->score;
}

std::string BonusAccount::applyInterestRate(double) {}
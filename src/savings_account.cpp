#include <iostream>
#include "../headers/savings_account.h"
using namespace std;

SavingsAccount::SavingsAccount(int id, double initialBalance) : BankAccount(id, initialBalance) {
    this->interestRate = 0;
}

SavingsAccount::~SavingsAccount() {}

double SavingsAccount::getInterestRate() const {
    return this->interestRate;
}

void SavingsAccount::applyInterestRate(double value) {
    double interest = this->getBalance() * (value / 100);
    this->credit(interest);
}

void SavingsAccount::addBonusCredit(double) {}
void SavingsAccount::addBonusTransfer(double) {}
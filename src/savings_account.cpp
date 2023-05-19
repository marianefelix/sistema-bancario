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

void SavingsAccount::applyInterestRate() {
    double interest = this->getBalance() * this->interestRate;
    this->credit(interest);
}
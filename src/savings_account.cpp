#include <iostream>
#include <sstream>
#include "../headers/savings_account.h"
using namespace std;

SavingsAccount::SavingsAccount(int id, double initialBalance) : BankAccount(id, initialBalance) {
    this->interestRate = 0;
}

SavingsAccount::~SavingsAccount() {}

double SavingsAccount::getInterestRate() const {
    return this->interestRate;
}

std::string SavingsAccount::applyInterestRate(double value) {
    double interest = this->getBalance() * (value / 100);
    this->credit(interest);
    string result = "Saldo atualizado: " + to_string(this->getBalance());
    return result;
}

void SavingsAccount::addBonusCredit(double) {}
void SavingsAccount::addBonusTransfer(double) {}
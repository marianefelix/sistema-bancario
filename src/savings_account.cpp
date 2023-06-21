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

std::string SavingsAccount::debit(double value) {
    double newBalance = this->getBalance() - value;

    if (newBalance > 0 && value >= 0) {
        this->setBalance(newBalance);
        string success = "Seu novo saldo é: " + to_string(this->getBalance());
        return success;
    }

    if(newBalance < 0){
        return "Não há saldo suficiente para debitar.";
    }

    return "Digite um valor maior ou igual a 0.";
}

std::string SavingsAccount::transfer(BankAccount& destination, double value) {
    double newBalance = this->getBalance() - value;

    if (newBalance > 0 && value >= 0) {
        this->debit(value);
        destination.credit(value);
    }

    if(newBalance < 0){
        return "Não há saldo suficiente para transferir.";
    }

    return "Digite um valor maior ou igual a 0.";
}

void SavingsAccount::addBonusCredit(double) {}
void SavingsAccount::addBonusTransfer(double) {}
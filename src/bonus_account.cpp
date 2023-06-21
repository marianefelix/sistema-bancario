#include <iostream>
#include <sstream>
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

std::string BonusAccount::credit(double value) {
    double newBalance = this->getBalance() + value;

    if (value >= 0) {
        this->setBalance(newBalance);
        addBonusCredit(value);
        string success = "Seu novo saldo é: " + to_string(this->getBalance()) + "  |  Seu bonus atualizado: " + to_string(this->getScore());
        return success;
    }
    return "Digite um valor maior ou igual a 0.";
}

std::string BonusAccount::transfer(BankAccount& destination, double value) {
    double newBalance = this->getBalance() - value;

    if (newBalance >= 0 && value >= 0) {
        this->debit(value);
        destination.credit(value);
        addBonusTransfer(value);
        string success = "Seu novo saldo é: " + to_string(this->getBalance()) + "  |  Seu bonus atualizado: " + to_string(this->getScore());
        return success;
    }

    if(newBalance < 0){
        return "Não há saldo suficiente para transferir.";
    }

    return "Digite um valor maior ou igual a 0.";
}

std::string BonusAccount::applyInterestRate(double) {}
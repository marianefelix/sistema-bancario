#include <iostream>
#include "../headers/bank_account.h"
using namespace std;

BankAccount::BankAccount(int id, double initialBalance) {
    this->accountID = id;
    this->balance = initialBalance;
}

BankAccount::~BankAccount() {}

int BankAccount::getAccountID() const {
    return this->accountID;
}

double BankAccount::getBalance() const {
    return this->balance;
}

void BankAccount::credit(double value) {
    this->balance = this->balance + value;
}

void BankAccount::debit(double value) {
    double newBalance = this->balance - value;

    if (newBalance > 0) {
        this->balance = newBalance;
    }
}

void BankAccount::transfer(BankAccount& destination, double value) {
    double newBalance = this->balance - value;

    if (newBalance > 0) {
        this->debit(value);
        destination.credit(value);
    }
}
#include <iostream>
#include "../headers/generic_account.h"
#include "../headers/bank_account.h"

GenericAccount::GenericAccount(int id, double initialBalance)
    : BankAccount(id, initialBalance) {}

GenericAccount::~GenericAccount() {}

std::string GenericAccount::applyInterestRate(double) {
    return "Essa conta não é uma Conta Poupança.";
}

void GenericAccount::addBonusCredit(double) {}
void GenericAccount::addBonusTransfer(double) {}

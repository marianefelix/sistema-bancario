#include <iostream>
#include "../headers/generic_account.h"
#include "../headers/bank_account.h"

GenericAccount::GenericAccount(int id, double initialBalance)
    : BankAccount(id, initialBalance) {}

GenericAccount::~GenericAccount() {}

void GenericAccount::applyInterestRate(double) {}
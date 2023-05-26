#include <vector>
#include <iostream>
#include "../headers/bank.h"
#include "../headers/bank_account.h"

using namespace std;

Bank::Bank() {}

Bank::~Bank() {
    for (BankAccount* account : this->accounts) {
        delete account;
    }
}

// Add an account to the bank
string Bank::addAccount(int accountID, double openingBalance) {
    for (BankAccount* account : this->accounts) {
        if (account->getAccountID() == accountID) {
            return "Essa conta já existe.";
        }
    }

    BankAccount* newAccount = new BankAccount(accountID, openingBalance);
    this->accounts.push_back(newAccount);

    return "Conta criada com sucesso!";
}

BankAccount* Bank::getAccountByID(int accountID) {
    for (BankAccount* account : this->accounts) {
        if (account->getAccountID() == accountID) {
            return account;
        }
    }

    return nullptr;
}
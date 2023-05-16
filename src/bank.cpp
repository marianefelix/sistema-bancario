#include <vector>
#include <iostream>
#include "../headers/bank.h"
#include "../headers/bank_account.h"

using namespace std;

Bank::Bank() {}
Bank::~Bank() {}

// Add an account to the bank
std::string Bank::addAccount(int accountID) {
    for (BankAccount account : this->accounts) {
        if (account.getAccountID() == accountID) {
            return "Essa conta já existe.";
        }
    }

    BankAccount newAccount(accountID, 0.0);
    this->accounts.push_back(newAccount);

    return "Conta criada com sucesso!";
}

BankAccount Bank::getAccountByID(int accountID) {
    for (BankAccount account : this->accounts) {
        if (account.getAccountID() == accountID) {
            return account;
        }
    }

    BankAccount errorAccount(-1, -1);
    return errorAccount;
}
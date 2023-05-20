#include <vector>
#include <iostream>
#include "../headers/bank.h"
#include "../headers/bank_account.h"
#include "../headers/generic_account.h"
#include "../headers/bonus_account.h"
#include "../headers/savings_account.h"

using namespace std;

Bank::Bank() {}

Bank::~Bank() {
    for (BankAccount* account : this->accounts) {
        delete account;
    }
}

// Add an account to the bank
string Bank::addAccount(int accountID) {
    for (BankAccount* account : this->accounts) {
        if (account->getAccountID() == accountID) {
            return "Essa conta já existe.";
        }
    }

    BankAccount* newAccount = new BankAccount(accountID, 0.0);
    this->accounts.push_back(newAccount);

    return "Conta Simples criada com sucesso!";
}

// Add an bonus account to the bank
string Bank::addBonusAccount(int accountID) {
    for (BankAccount* account : this->accounts) {
        if (account->getAccountID() == accountID) {
            return "Essa conta já existe.";
        }
    }

    BankAccount* newAccount = new BonusAccount(accountID, 0.0);
    this->accounts.push_back(newAccount);

    return "Conta Bonus criada com sucesso!";
}

// Add an savings account to the bank
string Bank::addSavingsAccount(int accountID) {
    for (BankAccount* account : this->accounts) {
        if (account->getAccountID() == accountID) {
            return "Essa conta já existe.";
        }
    }

    BankAccount* newAccount = new SavingsAccount(accountID, 0.0);
    this->accounts.push_back(newAccount);

    return "Conta Poupança criada com sucesso!";
}

BankAccount* Bank::getAccountByID(int accountID) {
    for (BankAccount* account : this->accounts) {
        if (account->getAccountID() == accountID) {
            return account;
        }
    }

    return nullptr;
}
#include <vector>
#include <iostream>
#include <sstream>
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

template<typename Base, typename T>
inline bool instanceof(const T *ptr) {
   return dynamic_cast<const Base*>(ptr) != nullptr;
}

// Add an account to the bank
string Bank::addAccount(int accountID, double openingBalance) {
    for (BankAccount* account : this->accounts) {
        if (account->getAccountID() == accountID) {
            return "Essa conta já existe.";
        }
    }

    BankAccount* newAccount = new GenericAccount(accountID, openingBalance);
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
string Bank::addSavingsAccount(int accountID, double openingBalance) {
    for (BankAccount* account : this->accounts) {
        if (account->getAccountID() == accountID) {
            return "Essa conta já existe.";
        }
    }

    BankAccount* newAccount = new SavingsAccount(accountID, openingBalance);
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

std::string Bank::getAccountType(BankAccount* account) {
    if (instanceof<GenericAccount>(account)) {
        return "Conta simples";
    }

    if (instanceof<BonusAccount>(account)) {
        return "Conta bônus";
    }

    return "Conta poupança";
}

std::vector<BankAccount*> Bank::getAccounts() {
    return this->accounts;
}

std::string Bank::consultAccount(int accountID) {
    BankAccount* account = getAccountByID(accountID);
    string result;

    if(account == nullptr) {
        result = "Essa conta não existe";
        return result;
    }

    string type = getAccountType(account);
    result = "Tipo: " + type + "  |  Saldo: " + to_string(account->getBalance()) + "  |  Número: " + to_string(account->getAccountID());

    if (type == "Conta bônus") {
      BonusAccount* bonusAccount = dynamic_cast<BonusAccount*>(account);
      result = result + "  |  Bônus: " + to_string(bonusAccount->getScore());
    }

    return result;
}

std::string Bank::consultAccountBalance(int accountID) {
    BankAccount* account = getAccountByID(accountID);
    string result;

    if(account == nullptr) {
        result = "Essa conta não existe";
        return result;
    }

    result = "O seu saldo é: " + to_string(account->getBalance());

    return result;
}
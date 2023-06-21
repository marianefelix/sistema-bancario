#include <iostream>
#include "../headers/bank_account.h"
#include "../headers/bank.h"
#include "../headers/savings_account.h"
#include "../headers/navigation_menu.h"
#include "../headers/savings_account.h"
#include "../headers/bonus_account.h"
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

void BankAccount::setBalance(double value) {
    this->balance = value;
}

std::string BankAccount::consultAccount(std::string type) {
    string result = "Tipo: " + type + "  |  Saldo: " + to_string(this->balance) + "  |  Número: " +  + to_string(this->accountID);
    return result;
}

std::string BankAccount::credit(double value) {
    if (value >= 0) {
        this->balance = this->balance + value;
        string success = "Seu novo saldo é: " + to_string(this->balance);
        return success;
    }
    return "Digite um valor maior ou igual a 0.";
}

std::string BankAccount::debit(double value) {
    if(value >= 0) {
        double newBalance = this->balance - value;

        if (newBalance >= -1000) {
            this->balance = newBalance;
            string success = "Seu novo saldo é: " + to_string(this->balance);
            return success;
        }
    }
    return "Digite um valor maior ou igual a 0.";
}

std::string BankAccount::transfer(BankAccount& destination, double value) {
    double newBalance = this->balance - value;

    if (newBalance >= 0 && value >= 0) {
        this->debit(value);
        destination.credit(value);
    }

    if(newBalance < 0){
        return "Não há saldo suficiente para transferir.";
    }
    
    return "Digite um valor maior ou igual a 0.";
}
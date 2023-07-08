#ifndef GENERIC_ACCOUNT_H
#define GENERIC_ACCOUNT_H

#include "bank_account.h"

class GenericAccount : public BankAccount {
  public:
    GenericAccount(int id, double initialBalance);
    virtual ~GenericAccount();
    virtual std::string applyInterestRate(double value);
    virtual void addBonusCredit(double value);
    virtual void addBonusTransfer(double value);
};

#endif
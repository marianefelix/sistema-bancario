#ifndef BANK_ACCOUNT_H
#define BANK_ACCOUNT_H

class BankAccount {
    private:
        int accountID;
        double balance;
    
    public:
        BankAccount(int id, double initialBalance); // constructor
        virtual ~BankAccount(); // destructor

        virtual void applyInterestRate(double value) = 0;

        virtual void addBonusCredit(double value) = 0;

        virtual void addBonusTransfer(double value) = 0;

        int getAccountID() const;

        double getBalance() const;

        void credit(double value);

        void debit(double value);

        void transfer(BankAccount& destination, double value);
};

#endif
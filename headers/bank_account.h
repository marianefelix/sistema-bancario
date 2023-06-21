#ifndef BANK_ACCOUNT_H
#define BANK_ACCOUNT_H

class BankAccount {
    private:
        int accountID;
        double balance;
    
    public:
        BankAccount(int id, double initialBalance); // constructor
        virtual ~BankAccount(); // destructor

        virtual std::string applyInterestRate(double value) = 0;

        virtual void addBonusCredit(double value) = 0;

        virtual void addBonusTransfer(double value) = 0;

        int getAccountID() const;

        double getBalance() const;

        void setBalance(double value);

        std::string consultAccount(std::string type);

        std::string credit(double value);

        virtual std::string debit(double value);

        virtual std::string transfer(BankAccount& destination, double value);
};

#endif
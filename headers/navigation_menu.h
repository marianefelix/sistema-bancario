#ifndef NAVIGATION_MENU_H
#define NAVIGATION_MENU_H

#include "bank.h"
#include "bank_account.h"

class NavigationMenu {
    private:
        int getAccountID();
        int getTypeAccount();

    public:
        NavigationMenu(); //constructor
        ~NavigationMenu(); //destructor

        void showOptions();

        void handleSelectedOption(Bank& bank, int selectedOption);

        void handleCreateAccount(Bank& bank);

        void handleCreateNormalAccount(Bank& bank);

        void handleCreateSavingsAccount(Bank& bank);

        void handleCreateBonusAccount(Bank& bank);

        void handleConsultAccount(Bank& bank);

        void handleGetBalance(Bank& bank);

        void handleCredit(Bank& bank);

        void handleDebit(Bank& bank);

        void handleTransfer(Bank& bank);

        double handleOpeningBalance();

        void handleInterestRate(Bank& bank);
};

#endif
#ifndef NAVIGATION_MENU_H
#define NAVIGATION_MENU_H

#include "bank.h"
#include "bank_account.h"

class NavigationMenu {
    private:
        int getAccountID();

    public:
        NavigationMenu(); //constructor
        ~NavigationMenu(); //destructor

        void showOptions();

        void handleSelectedOption(Bank& bank, int selectedOption);

        void handleCreateAccount(Bank& bank);

        void handleGetBalance(Bank& bank);

        void handleCredit(Bank& bank);

        void handleDebit(Bank& bank);

        void handleTransfer(Bank& bank);

        double handleOpeningBalance();
};

#endif
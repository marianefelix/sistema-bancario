#ifndef NAVIGATION_MENU_H
#define NAVIGATION_MENU_H

#include "bank.h"
#include "bank_account.h"

class NavigationMenu {
    private:
        int getAccountID();

    public:
        NavigationMenu(); //construtor
        ~NavigationMenu(); //destrutor

        void showOptions();

        void handleSelectedOption(Bank& bank);

        void handleCreateAccount(Bank& bank);

        void handleGetBalance(Bank& bank);

        void handleCredit(Bank& bank);

        void handleDebit(Bank& bank);

        void handleTransfer(Bank& bank);
};

#endif
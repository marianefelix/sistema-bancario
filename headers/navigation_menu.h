#ifndef NAVIGATION_MENU_H
#define NAVIGATION_MENU_H

#include "bank.h"
#include "bank_account.h"
#include <pistache/client.h>
#include "json.hpp"

using namespace Pistache;
using namespace std;
using json = nlohmann::json;

class NavigationMenu {
    private:
        int getAccountID();
        int getAccountType();
        Http::Experimental::Client client;

    public:
        NavigationMenu(); //constructor
        ~NavigationMenu(); //destructor

        void showOptions();
        void handleSelectedOption(int selectedOption);
        void handleCreateAccount();
        void handleConsultAccount();
        void handleGetBalance();
        double handleOpeningBalance();
        void handleCredit();
        void handleDebit();
        void handleTransfer();
        void handleInterestRate();
};

#endif
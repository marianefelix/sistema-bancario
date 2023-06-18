#include <iostream>
#include "../headers/bank.h"
#include "../headers/navigation_menu.h"
#include "../headers/bank_api.h"

using namespace std;

int main() {
    Address addr = new Address(Ipv4::any(), Port(8080));
    BankAPI api = new BankAPI(addr);
    
    api.init();
    api.start();

    cout << "Server is running on port 8080..." << endl;
    cin.ignore();

    NavigationMenu navigationMenu;
    Bank bank;
    int selectedOption = 0;

    do {
        navigationMenu.showOptions();
        cin >> selectedOption;
        navigationMenu.handleSelectedOption(bank, selectedOption);
    } while (selectedOption < 8);

    api.shutdown();

    return 0;
}
#include <iostream>
#include "../headers/bank.h"
#include "../headers/navigation_menu.h"
using namespace std;

int main() {
    // Iniciate app
    NavigationMenu navigationMenu;

    // Iniciate bank
    Bank bank;
    
    // After the app is launched, the menu should be called
    int selectedOption;

    do {
        navigationMenu.showOptions();
        std::cin >> selectedOption;
    } while (selectedOption != 6);
    
    // navigationMenu.showOptions();

    navigationMenu.handleSelectedOption(bank, selectedOption);

    return 0;
}
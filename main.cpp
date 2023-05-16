#include <iostream>
#include "src/bank.cpp"
#include "src/navigation_menu.cpp"
using namespace std;

int main() {
    // Iniciate app
    NavigationMenu navigationMenu;

    // Iniciate bank
    Bank bank;
    
    // After the app is launched, the menu should be called
    // int selectedOption;

    // do {
    //     navigationMenu.showOptions();
    //     std::cin >> selectedOption;
    // } while (selectedOption != 6) {
    
    navigationMenu.showOptions();

    navigationMenu.handleSelectedOption(bank);

    return 0;
}
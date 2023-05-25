#include <iostream>
#include "../headers/bank.h"
#include "../headers/navigation_menu.h"
using namespace std;

int main() {
    NavigationMenu navigationMenu;

    Bank bank;

    int selectedOption = 0;

    do {
        navigationMenu.showOptions();
        std::cin >> selectedOption;
        navigationMenu.handleSelectedOption(bank, selectedOption);
    } while (selectedOption < 7);

    return 0;
}
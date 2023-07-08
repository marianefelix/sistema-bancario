#include <iostream>
#include "../headers/bank.h"
#include "../headers/navigation_menu.h"
#include "../headers/bank_api.h"

using namespace std;

int main() {
    Address addr(Ipv4::any(), Port(8080));
    BankAPI api(addr);

    auto apiThread = [&api]() {
        api.init();
        api.start();
    };

    thread apiExecution(apiThread);

    NavigationMenu navigationMenu;
    int selectedOption = 0;

    do {
        navigationMenu.showOptions();
        cin >> selectedOption;
        navigationMenu.handleSelectedOption(selectedOption);
    } while (selectedOption < 8);

    api.shutdown();
    apiExecution.join();

    return 0;
}
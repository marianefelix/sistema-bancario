#include <iostream>
#include "bank.cpp"
#include "bank_account.cpp"

using namespace std;

class NavigationMenu {
public:
  void showOptions() {
    cout << "---------- Menu ----------" << endl;
    cout << "1 - Criar conta" << endl;
    cout << "2 - Consultar saldo" << endl;
    cout << "3 - Creditar" << endl;
    cout << "4 - Debitar" << endl;
    cout << "5 - Realizar transferência" << endl;
    cout << "6 - Sair" << endl;
    cout << "---------------------------" << endl;
  }

  void handleSelectedOption(Bank& bank) {
    int selectedOption;
    cin >> selectedOption;

    switch(selectedOption) {
      case 1:
        handleCreateAccount();
        break;
      case 2:
        handleGetBalance();
        break;
      case 3:
        handleCredit();
        break;
      case 4:
        handleDebit();
        break;
      case 5:
        handleTransfer();
        break;
      default:
        cout << "Opção inválida" << endl;
        break;
    }
  }

  int getAccountID() {
    int accountID;

    cout << "Digite o número da conta: " << endl;
    cin >> accountID;

    return accountID;
  }

  void handleCreateAccount(Bank& bank) {
    int accountID = getAccountID();
    string response = bank.addAccount(accountID)
    cout << response << endl;
  }

  void handleGetBalance() {
    int accountID = getAccountID();
    BankAccount account = bank.getAccountByID(accountID);

    if (account.getAccountID() == -1) {
        cout << "Essa conta não existe" << endl;
    } else {
        double accountBalance = account.getBalance();
        cout << "O saldo da sua conta é: " << accountBalance <<  endl;
    }
  }

  void handleDebit() {}
  
  void handleTransfer() {}
}

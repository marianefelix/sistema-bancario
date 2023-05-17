#include <iostream>
#include "../headers/bank.h"
#include "../headers/bank_account.h"
#include "../headers/navigation_menu.h"

using namespace std;

NavigationMenu::NavigationMenu() {}
NavigationMenu::~NavigationMenu() {}

int NavigationMenu::getAccountID() {
  int accountID;

  cout << "Digite o número da conta: " << endl;
  cin >> accountID;

  return accountID;
}

void NavigationMenu::showOptions() {
  cout << "---------- Menu ----------" << endl;
  cout << "1 - Criar conta" << endl;
  cout << "2 - Consultar saldo" << endl;
  cout << "3 - Creditar" << endl;
  cout << "4 - Debitar" << endl;
  cout << "5 - Realizar transferência" << endl;
  cout << "6 - Sair" << endl;
  cout << "---------------------------" << endl;
}

void NavigationMenu::handleSelectedOption(Bank& bank, int selectedOption) {
  switch(selectedOption) {
    case 1:
      handleCreateAccount(bank);
      break;
    case 2:
      handleGetBalance(bank);
      break;
    case 3:
      handleCredit(bank);
      break;
    case 4:
      handleDebit(bank);
      break;
    case 5:
      handleTransfer(bank);
      break;
    case 6:
      cout << "Seção encerrada" << endl;
      break;
    default:
      cout << "Opção inválida" << endl;
      break;
  }
}

void NavigationMenu::handleCreateAccount(Bank& bank) {
  int accountID = getAccountID();
  string response = bank.addAccount(accountID);
  cout << response << endl;
}

void NavigationMenu::handleGetBalance(Bank& bank) {
  int accountID = getAccountID();
  BankAccount account = bank.getAccountByID(accountID);

  if (account.getAccountID() == -1) {
      cout << "Essa conta não existe" << endl;
  } else {
      double accountBalance = account.getBalance();
      cout << "O saldo da sua conta é: " << accountBalance <<  endl;
  }
}

void NavigationMenu::handleCredit(Bank& bank) {
  int accountID = getAccountID();
  double value;

  cout << "Digite o valor a ser creditado: " << endl;
  cin >> value;

  BankAccount account = bank.getAccountByID(accountID);
  if (account.getAccountID() == -1) {
      cout << "Essa conta não existe" << endl;
  } else {
      account.credit(value);
      double accountBalance = account.getBalance();
      cout << "Seu novo saldo é: " << accountBalance <<  endl;
  }
}

void NavigationMenu::handleDebit(Bank& bank) {
  int accountID = getAccountID();
  double value;

  cout << "Digite o valor a ser debitado: " << endl;
  cin >> value;

  BankAccount account = bank.getAccountByID(accountID);
  if (account.getAccountID() == -1) {
      cout << "Essa conta não existe" << endl;
  } else {
      account.debit(value);
      double accountBalance = account.getBalance();
      cout << "Seu novo saldo é: " << accountBalance <<  endl;
  }
}
  
void NavigationMenu::handleTransfer(Bank& bank) {
  int originAccountID, destinationAccountID;
  double value;

  cout << "Digite o número da conta de origem: " << endl;
  cin >> originAccountID;

  cout << "Digite o número da conta de destino: " << endl;
  cin >> destinationAccountID;

  cout << "Digite o valor a ser transferido: " << endl;
  cin >> value;

  BankAccount originAccount = bank.getAccountByID(originAccountID);
  BankAccount destinationAccount = bank.getAccountByID(destinationAccountID);

  if (originAccount.getAccountID() == -1 || destinationAccount.getAccountID() == -1) {
      cout << "Erro ao encontrar contas. Por favor, insira um número válido." << endl;
  } else {
      originAccount.transfer(destinationAccount, value);
      double accountBalance = originAccount.getBalance();
      cout << "Seu novo saldo é: " << accountBalance <<  endl;
  }
}
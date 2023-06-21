#include <iostream>
#include <string>
#include <sstream>
#include "../headers/bank.h"
#include "../headers/bank_account.h"
#include "../headers/savings_account.h"
#include "../headers/navigation_menu.h"
#include "../headers/savings_account.h"
#include "../headers/bonus_account.h"

using namespace std;

NavigationMenu::NavigationMenu() {}
NavigationMenu::~NavigationMenu() {}

int NavigationMenu::getAccountID() {
  int accountID;

  cout << "Digite o número da conta: " << endl;
  cin >> accountID;

  return accountID;
}

int NavigationMenu::getTypeAccount() {
  int typeAccount;

  cout << "---------------------------" << endl;
  cout << "Escolha o tipo de conta:" << endl;
  cout << "1 - Conta Simples" << endl;
  cout << "2 - Conta Poupança" << endl;
  cout << "3 - Conta Bonus" << endl;
  cin >> typeAccount;
  cout << "---------------------------" << endl;

  return typeAccount;
}

void NavigationMenu::showOptions() {
  cout << "---------- Menu ----------" << endl;
  cout << "1 - Criar conta" << endl;
  cout << "2 - Consultar conta" << endl;
  cout << "3 - Consultar saldo" << endl;
  cout << "4 - Creditar" << endl;
  cout << "5 - Debitar" << endl;
  cout << "6 - Realizar transferência" << endl;
  cout << "7 - Render Juros" << endl;
  cout << "8 - Sair" << endl;
  cout << "---------------------------" << endl;
}

void NavigationMenu::handleSelectedOption(Bank& bank, int selectedOption) {
  switch(selectedOption) {
    case 1:
      handleCreateAccount(bank);
      break;
    case 2:
      handleConsultAccount(bank);
      break;
    case 3:
      handleGetBalance(bank);
      break;
    case 4:
      handleCredit(bank);
      break;
    case 5:
      handleDebit(bank);
      break;
    case 6:
      handleTransfer(bank);
      break;
    case 7:
      handleInterestRate(bank);
      break;
    case 8:
      cout << "Seção encerrada" << endl;
      break;
    default:
      cout << "Opção inválida" << endl;
      break;
  }
}

void NavigationMenu::handleCreateAccount(Bank& bank) {
  int typeAccount = getTypeAccount();

  switch(typeAccount) {
    case 1:
      handleCreateNormalAccount(bank);
      break;
    case 2:
      handleCreateSavingsAccount(bank);
      break;
    case 3:
      handleCreateBonusAccount(bank);
      break;
    default:
      cout << "Opção inválida" << endl;
      break;
  }
}

void NavigationMenu::handleCreateNormalAccount(Bank& bank) {
  int accountID = getAccountID();
  double openingBalance = handleOpeningBalance();
  string response = bank.addAccount(accountID, openingBalance);
  cout << response << endl;
}

void NavigationMenu::handleCreateSavingsAccount(Bank& bank) {
  int accountID = getAccountID();
  double openingBalance = handleOpeningBalance();
  string response = bank.addSavingsAccount(accountID, openingBalance);
  cout << response << endl;
}

void NavigationMenu::handleCreateBonusAccount(Bank& bank) {
  int accountID = getAccountID();
  string response = bank.addBonusAccount(accountID);
  cout << response << endl;
}

void NavigationMenu::handleConsultAccount(Bank& bank) {
  int accountID = getAccountID();
  BankAccount* account = bank.getAccountByID(accountID);

 if (account == nullptr) {
    cout << "Essa conta não existe" << endl;
  } else {
    string result = bank.consultAccount(account);
    cout << result << endl;
  }
}

void NavigationMenu::handleGetBalance(Bank& bank) {
  int accountID = getAccountID();
  BankAccount* account = bank.getAccountByID(accountID);

  if (account == nullptr) {
      cout << "Essa conta não existe" << endl;
  } else {
      double accountBalance = account->getBalance();
      cout << "O saldo da sua conta é: " << accountBalance <<  endl;
  }
}

void NavigationMenu::handleCredit(Bank& bank) {
  int accountID = getAccountID();
  double value;

  cout << "Digite o valor a ser creditado: " << endl;
  cin >> value;

  BankAccount* account = bank.getAccountByID(accountID);

  if (account == nullptr) {
      cout << "Essa conta não existe" << endl;
  } else {
    string result = account->credit(value);
    cout << result << endl;
  }
}

void NavigationMenu::handleDebit(Bank& bank) {
  int accountID = getAccountID();
  double value;

  cout << "Digite o valor a ser debitado: " << endl;
  cin >> value;

  BankAccount* account = bank.getAccountByID(accountID);

  if (account == nullptr) {
      cout << "Essa conta não existe" << endl;
  } else {
      string result = account->debit(value);
      cout << result << endl;
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

  BankAccount* originAccount = bank.getAccountByID(originAccountID);
  BankAccount* destinationAccount = bank.getAccountByID(destinationAccountID);

  if (originAccount == nullptr || destinationAccount == nullptr) {
      cout << "Erro ao encontrar contas. Por favor, insira um número válido." << endl;
  } else {
      string result = originAccount->transfer(*destinationAccount, value);
      cout << result << endl;
  }
}

void NavigationMenu::handleInterestRate(Bank& bank) {
  int accountID = getAccountID();
  double interestRate;

  BankAccount* account = bank.getAccountByID(accountID);

  SavingsAccount* savingsAccount = dynamic_cast<SavingsAccount*>(account);

  if (savingsAccount == nullptr) {
    cout << "Essa conta não é uma Conta Poupança." << endl;
  } else {
    cout << "Informe a taxa de juros:" << endl;
    cin >> interestRate;

    string result = savingsAccount->applyInterestRate(interestRate);

    cout << result << endl;
  }
}

double NavigationMenu::handleOpeningBalance() {
  double openingBalance;
  string userInput;
    
  while(true) {
    cout << "Digite o saldo inicial da conta: " << endl;
    cin >> userInput;

    istringstream iss(userInput);
    if(iss >> openingBalance) {
      break;  
    } else {
      cout << "Entrada inválida. Por favor, insira um valor numérico." << endl;
    }
  }

  return openingBalance;
}
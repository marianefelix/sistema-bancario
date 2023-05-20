#include <iostream>
#include "../headers/bank.h"
#include "../headers/bank_account.h"
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
  cout << "2 - Consultar saldo" << endl;
  cout << "3 - Creditar" << endl;
  cout << "4 - Debitar" << endl;
  cout << "5 - Realizar transferência" << endl;
  cout << "6 - Render Juros" << endl;
  cout << "7 - Sair" << endl;
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
      handleInterestRate(bank);
      break;
    case 7:
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
  string response = bank.addAccount(accountID);
  cout << response << endl;
}

void NavigationMenu::handleCreateSavingsAccount(Bank& bank) {
  int accountID = getAccountID();
  string response = bank.addSavingsAccount(accountID);
  cout << response << endl;
}

void NavigationMenu::handleCreateBonusAccount(Bank& bank) {
  int accountID = getAccountID();
  string response = bank.addBonusAccount(accountID);
  cout << response << endl;
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

  BonusAccount* bonusAccount = dynamic_cast<BonusAccount*>(account);

  if (account == nullptr) {
      cout << "Essa conta não existe" << endl;
  } else {
      account->credit(value);
      double accountBalance = account->getBalance();
      cout << "Seu novo saldo é: " << accountBalance <<  endl;
      
      if(bonusAccount != nullptr) {
        int bonusValue = bonusAccount->getScore();
        bonusAccount->addBonusCredit(value);
        bonusValue = bonusAccount->getScore() - bonusValue;
        if(bonusValue > 0) {
          cout << "Seu bonus aumentou " << bonusValue << " ponto(s)! Seu bonus agora é: " << bonusAccount->getScore() << endl;
        }
      }
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
      account->debit(value);
      double accountBalance = account->getBalance();
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

  BankAccount* originAccount = bank.getAccountByID(originAccountID);
  BankAccount* destinationAccount = bank.getAccountByID(destinationAccountID);

  BonusAccount* bonusAccount = dynamic_cast<BonusAccount*>(destinationAccount);

  if (originAccount == nullptr || destinationAccount == nullptr) {
      cout << "Erro ao encontrar contas. Por favor, insira um número válido." << endl;
  } else {
      originAccount->transfer(*destinationAccount, value);
      double accountBalance = originAccount->getBalance();
      cout << "Seu novo saldo é: " << accountBalance << endl;
      
      if(bonusAccount != nullptr) {
        int bonusValue = bonusAccount->getScore();
        bonusAccount->addBonusTransfer(value);
        bonusValue = bonusAccount->getScore() - bonusValue;
        if(bonusValue > 0) {
          cout << "O bonus da conta de destino aumentou " << bonusValue << " ponto(s)! Seu bonus agora é: " << bonusAccount->getScore() << endl;
        }
      }
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

    savingsAccount->applyInterestRate(interestRate);

    cout << "Saldo atualizado: " << savingsAccount->getBalance() << endl;
  }
}
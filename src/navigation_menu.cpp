#include <iostream>
#include <string>
#include <sstream>
#include "../headers/navigation_menu.h"

NavigationMenu::NavigationMenu() {
}

NavigationMenu::~NavigationMenu() {}

int NavigationMenu::getAccountID() {
  int accountID;

  cout << "Digite o número da conta: " << endl;
  cin >> accountID;

  return accountID;
}

int NavigationMenu::getAccountType() {
  int accountType;

  cout << "---------------------------" << endl;
  cout << "Escolha o tipo de conta:" << endl;
  cout << "1 - Conta Simples" << endl;
  cout << "2 - Conta Poupança" << endl;
  cout << "3 - Conta Bonus" << endl;
  cin >> accountType;
  cout << "---------------------------" << endl;

  return accountType;
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

void NavigationMenu::handleSelectedOption(int selectedOption) {
  switch(selectedOption) {
    case 1:
      handleCreateAccount();
      break;
    case 2:
      handleConsultAccount();
      break;
    case 3:
      handleGetBalance();
      break;
    case 4:
      handleCredit();
      break;
    case 5:
      handleDebit();
      break;
    case 6:
      handleTransfer();
      break;
    case 7:
      handleInterestRate();
      break;
    case 8:
      cout << "Seção encerrada" << endl;
      break;
    default:
      cout << "Opção inválida" << endl;
      break;
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

void NavigationMenu::handleCreateAccount() {
  client.init();

  int accountType = getAccountType();
  int accountID = getAccountID();
  json accountData;

  accountData["type"] = accountType;
  accountData["id"] = accountID;

  if (accountType == 1 || accountType == 2) {
    accountData["openingBalance"] = handleOpeningBalance();
  }

  auto response = client.post("http://localhost:8080/bank/account")
    .body(accountData.dump())
    .send();

  response.then(
    [&](Http::Response res) {
      if (res.code() == Http::Code::Ok) {
        cout << res.body() << endl;
      } else {
        cout << "Erro: " << res.body() << endl;
      }
    },
    Async::Throw
  );
}

void NavigationMenu::handleConsultAccount() {
  int accountID = getAccountID();

  auto response = client
  .get("http://localhost:8080/bank/account/" + to_string(accountID))
  .send();

  response.then(
    [&](Http::Response res) {
      if (res.code() == Http::Code::Ok) {
        cout << res.body() << endl;
      } else {
        cout << "Erro: " << res.body() << endl;
      }
    },
    Async::Throw
  );
}

void NavigationMenu::handleGetBalance() {
  int accountID = getAccountID();

  auto response = client
  .get("http://localhost:8080/bank/account/" + to_string(accountID) + "/balance")
  .send();

  response.then(
    [&](Http::Response res) {
      if (res.code() == Http::Code::Ok) {
        json responseBody = json::parse(res.body());
        double accountBalance = responseBody["balance"];
        
        cout << "O saldo da sua conta é: " << accountBalance <<  endl;
      } else {
        cout << "Erro: " << res.body() << endl;
      }
    },
    Async::Throw
  );
}

void NavigationMenu::handleCredit() {
  int accountID = getAccountID();
  double value;

  cout << "Digite o valor a ser creditado: " << endl;
  cin >> value;

  json data;
  data["credit"] = value;


  auto response = client.put("http://localhost:8080/bank/account/" + to_string(accountID) + "/credit")
    .body(data.dump())
    .send();

  response.then(
    [&](Http::Response res) {
      if (res.code() == Http::Code::Ok) {
        cout << res.body() << endl;
      } else {
        cout << "Erro: " << res.body() << endl;
      }
    },
    Async::Throw
  );
}

void NavigationMenu::handleDebit() {
  int accountID = getAccountID();
  double value;

  cout << "Digite o valor a ser debitado: " << endl;
  cin >> value;

  json data;
  data["debit"] = value;

  auto response = client.put("http://localhost:8080/bank/account/" + to_string(accountID) + "/debit")
    .body(data.dump())
    .send();

  response.then(
    [&](Http::Response res) {
      if (res.code() == Http::Code::Ok) {
        cout << res.body() << endl;
      } else {
        cout << "Erro: " << res.body() << endl;
      }
    },
    Async::Throw
  );
}

void NavigationMenu::handleTransfer() {
  int originAccountID, destinationAccountID;
  double value;

  cout << "Digite o número da conta de origem: " << endl;
  cin >> originAccountID;

  cout << "Digite o número da conta de destino: " << endl;
  cin >> destinationAccountID;

  cout << "Digite o valor a ser transferido: " << endl;
  cin >> value;

  json transferData;
  transferData["from"] = originAccountID;
  transferData["to"] = destinationAccountID;
  transferData["amount"] = value;

  auto response = client.put("http://localhost:8080/bank/account/transfer")
    .body(transferData.dump())
    .send();

  response.then(
    [&](Http::Response res) {
      if (res.code() == Http::Code::Ok) {
        cout << res.body() << endl;
      } else {
        cout << "Erro: " << res.body() << endl;
      }
    },
    Async::Throw
  );
}

void NavigationMenu::handleInterestRate() {
  double rate;

  cout << "Informe a taxa de juros:" << endl;
  cin >> rate;

  json data;
  data["rate"] = rate;

  auto response = client.put("http://localhost:8080/bank/account/income")
    .body(data.dump())
    .send();

  response.then(
    [&](Http::Response res) {
      if (res.code() == Http::Code::Ok) {
        cout << res.body() << endl;
      } else {
        cout << "Erro: " << res.body() << endl;
      }
    },
    Async::Throw
  );
}
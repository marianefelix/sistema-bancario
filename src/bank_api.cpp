#include "../headers/bank_api.h"

using namespace Pistache;


BankAPI::BankAPI(Address addr) : httpEndpoint(std::make_shared<Http::Endpoint>(addr)) {}

void BankAPI::init(size_t thr) {
    auto opts = Http::Endpoint::options().threads(static_cast<int>(thr));
    httpEndpoint->init(opts);
    setupRoutes();
}

void BankAPI::start() {
    cout << "Server is running on port 8080..." << endl;
    httpEndpoint->setHandler(router.handler());
    httpEndpoint->serve();
}

void BankAPI::shutdown() {
    httpEndpoint->shutdown();
}

void BankAPI::setupRoutes() {
    using namespace Rest;

    // Route to create an account
    Routes::Post(router, "/accounts/:accountID/:accountType/:accountOpeningBalance", Routes::bind(&BankAPI::createAccount, this));

    // Route to consult an account
    Routes::Get(router, "/accounts/:accountID", Routes::bind(&BankAPI::consultAccount, this));

    // Route to consult the balance of an account
    Routes::Get(router, "/accounts/:accountID/balance", Routes::bind(&BankAPI::consultAccountBalance, this));

    // Route to credit an account
    Routes::Put(router, "/accounts/:accountID/credit", Routes::bind(&BankAPI::creditAccount, this));

    // // Route to debit an account
    // Routes::Post(router, "/accounts/:accountID/debit", Routes::bind(&BankAPI::debitAccount, this));

    // // Route to transfer between accounts
    // Routes::Post(router, "/accounts/:originAccountID/transfer/:destinationAccountID", Routes::bind(&BankAPI::transferBetweenAccounts, this));

    // // Route to apply interest rate to an account
    // Routes::Post(router, "/accounts/:accountID/debit", Routes::bind(&BankAPI::debitAccount, this));

}

void BankAPI::createAccount(const Rest::Request& request, Http::ResponseWriter response) {
    int accountID = std::stoi(request.param(":accountID").as<std::string>());
    int accountType = std::stoi(request.param(":accountType").as<std::string>());
    int accountOpeningBalance = std::stoi(request.param(":accountOpeningBalance").as<std::string>());
    std::string result;
    
    switch(accountType) {
    case 1:
      result = bank.addAccount(accountID, accountOpeningBalance);
      response.send(Http::Code::Ok, result);
      break;
    case 2:
      result = bank.addSavingsAccount(accountID, accountOpeningBalance);
      response.send(Http::Code::Ok, result);
      break;
    case 3:
      result = bank.addBonusAccount(accountID);
      response.send(Http::Code::Ok, result);
      break;
    default:
      result = "Opção inválida";
      response.send(Http::Code::Internal_Server_Error, result);
      break;
    }
    
    //response.send(Http::Code::Ok, result);
}

void BankAPI::consultAccount(const Rest::Request& request, Http::ResponseWriter response) {
    int accountID = std::stoi(request.param(":accountID").as<std::string>());
    BankAccount* account = bank.getAccountByID(accountID);
    //int accountType = bank.getAccountTypeInt();


    if(account == nullptr) {
        response.send(Http::Code::Not_Found, "Conta não encontrada");
    } else {
        json accountJson;
        accountJson["id"] = account->getAccountID();
        accountJson["type"] = bank.getAccountType(account);
        accountJson["balance"] = account->getBalance();
        response.headers().add<Http::Header::ContentType>(MIME(Application, Json));
        response.send(Http::Code::Ok, accountJson.dump());
    }
}

void BankAPI::consultAccountBalance(const Rest::Request& request, Http::ResponseWriter response) {
    int accountID = std::stoi(request.param(":accountID").as<std::string>());
    BankAccount* account = bank.getAccountByID(accountID);

    if(account == nullptr) {
        response.send(Http::Code::Not_Found, "Conta não encontrada");
    } else {
        json accountJson;
        accountJson["balance"] = account->getBalance();
        response.headers().add<Http::Header::ContentType>(MIME(Application, Json));
        response.send(Http::Code::Ok, accountJson.dump());
    }
}

void BankAPI::creditAccount(const Rest::Request& request, Http::ResponseWriter response) {
    int accountID = std::stoi(request.param(":accountID").as<std::string>());
    double value = std::stod(request.body());

    BankAccount* account = bank.getAccountByID(accountID);

    if(account == nullptr) {
        response.send(Http::Code::Not_Found, "Conta não encontrada");
    } else {
        account->credit(value);
        response.send(Http::Code::Ok, "Crédito realizado com sucesso");
    }
}

// void debitAccount(const Rest::Request& request, Http::ResponseWriter response) {
//     int accountID = std::stoi(request.param(":accountID").as<std::string>());
//     double value = std::stod(request.body());

//     BankAccount account = bank.getAccountByID(accountID);

//     if(account.getAccountID() == -1) {
//         response.send(Http::Code::NotFound, "Conta não encontrada");
//     } else {
//         account.debit(value);
//         response.send(Http::Code::Ok, "Débito realizado com sucesso");
//     }
// }

// void transferBetweenAccounts(const Rest::Request& request, Http::ResponseWriter response) {
//     int originAccountID = std::stoi(request.param(":originAccountID").as<std::string>());
//     int destinationAccountID = std::stoi(request.param(":destinationAccountID").as<std::string>());
//     double value = std::stod(request.body());

//     BankAccount originAccount = bank.getAccountByID(originAccountID);
//     BankAccount destinationAccount = bank.getAccountByID(destinationAccountID);

//     if(originAccount.getAccountID() == -1 || destinationAccount.getAccountID() == -1) {
//         response.send(Http::Code::NotFound, "Conta(s) não encontrada(s)");
//     } else {
//         originAccount.transfer(destinationAccount, value);
//         response.send(Http::Code::Ok, "Transferência realizada com sucesso");
//     }
// }
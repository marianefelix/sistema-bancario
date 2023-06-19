#include "../headers/bank_api.h"

using namespace Pistache;
//using json = nlohmann::json;


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
    Routes::Post(router, "/accounts", Routes::bind(&BankAPI::createAccount, this));

    // // Route to consult an account
    // Routes::Post(router, "/accounts/:accountID", Routes::bind(&BankAPI::consultAccount, this));

    // // Route to consult the balance of an account
    // Routes::Get(router, "/accounts/:accountID/balance", Routes::bind(&BankAPI::getAccountBalance, this));

    // // Route to credit an account
    // Routes::Post(router, "/accounts/:accountID/credit", Routes::bind(&BankAPI::creditAccount, this));

    // // Route to debit an account
    // Routes::Post(router, "/accounts/:accountID/debit", Routes::bind(&BankAPI::debitAccount, this));

    // // Route to transfer between accounts
    // Routes::Post(router, "/accounts/:originAccountID/transfer/:destinationAccountID", Routes::bind(&BankAPI::transferBetweenAccounts, this));

    // // Route to apply interest rate to an account
    // Routes::Post(router, "/accounts/:accountID/debit", Routes::bind(&BankAPI::debitAccount, this));

}

void BankAPI::createAccount(const Rest::Request& request, Http::ResponseWriter response) {
    int accountID = std::stoi(request.param(":accountID").as<std::string>());
    //int accountType = std::stoi(request.param(":accountType").as<std::string>());
    int accountOpeningBalance = std::stoi(request.param(":accountOpeningBalance").as<std::string>());
    std::string result = bank.addAccount(accountID, accountOpeningBalance);
    
    // switch(typeAccount) {
    // case 1:
    //   result = Bank::addAccount(accountID, openingBalance);
    //   break;
    // case 2:
    //   result = bank.addSavingsAccount(accountID, openingBalance);
    //   break;
    // case 3:
    //   result = bank.addBonusAccount(accountID);
    //   break;
    // default:
    //   break;
    // }
    
    response.send(Http::Code::Ok, result);
}

// void consultAccount(const Rest::Request& request, Http::ResponseWriter response) {
//     int accountID = std::stoi(request.param(":accountID").as<std::string>());
//     BankAccount account = bank.getAccountByID(accountID);
//     if (account.getAccountID() == -1) {
//         response.send(Http::Code::NotFound, "Conta não encontrada");
//     } else {
//         json account;
//         account["balance"] = account.getBalance();
//         response.send(Http::Code::Ok, accountBalance.dump());
//     }
// }

// void getAccountBalance(const Rest::Request& request, Http::ResponseWriter response) {
//     int accountID = std::stoi(request.param(":accountID").as<std::string>());
    
//     BankAccount account = bank.getAccountByID(accountID);
    
//     if(account.getAccountID() == -1) {
//         response.send(Http::Code::NotFound, "Conta não encontrada");
//     } else {
//         json accountBalance;
//         accountBalance["balance"] = account.getBalance();
//         response.send(Http::Code::Ok, accountBalance.dump());
//     }
// }

// void creditAccount(const Rest::Request& request, Http::ResponseWriter response) {
//     int accountID = std::stoi(request.param(":accountID").as<std::string>());
//     double value = std::stod(request.body());

//     BankAccount account = bank.getAccountByID(accountID);

//     if(account.getAccountID() == -1) {
//         response.send(Http::Code::NotFound, "Conta não encontrada");
//     } else {
//         account.credit(value);
//         response.send(Http::Code::Ok, "Crédito realizado com sucesso");
//     }
// }

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
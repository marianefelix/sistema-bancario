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
    Routes::Post(router, "/bank/account", Routes::bind(&BankAPI::createAccount, this));

    // Route to consult an account
    Routes::Get(router, "/bank/account/:accountID", Routes::bind(&BankAPI::consultAccount, this));

    // Route to consult the balance of an account
    Routes::Get(router, "/bank/account/:accountID/balance", Routes::bind(&BankAPI::consultAccountBalance, this));

    // Route to credit an account
    Routes::Put(router, "/bank/account/:accountID/credit", Routes::bind(&BankAPI::creditAccount, this));

    // Route to debit an account
    Routes::Put(router, "/bank/account/:accountID/debit", Routes::bind(&BankAPI::debitAccount, this));

    // Route to transfer between accounts
    Routes::Put(router, "/bank/account/transfer", Routes::bind(&BankAPI::transferBetweenAccounts, this));

    // Route to apply income to an account
    Routes::Put(router, "/bank/account/income", Routes::bind(&BankAPI::income, this));

}

// TODO: enhance logic to remove code repetitions
void BankAPI::createAccount(const Rest::Request& request, Http::ResponseWriter response) {
    json payload = json::parse(request.body());
    
    int accountType = payload["type"];
    int accountID = payload["id"];
    double accountOpeningBalance = payload["openingBalance"].get<double>();
    std::string result;
    
    switch(accountType) {
    case 1:
        result = bank.addAccount(accountID, accountOpeningBalance);
        "Essa conta já existe." == result ? response.send(Http::Code::Bad_Request, result) : response.send(Http::Code::Ok, result);
      break;
    case 2:
        result = bank.addSavingsAccount(accountID, accountOpeningBalance);
        "Essa conta já existe." == result ? response.send(Http::Code::Bad_Request, result) : response.send(Http::Code::Ok, result);
      break;
    case 3:
        result = bank.addBonusAccount(accountID);
        "Essa conta já existe." == result ? response.send(Http::Code::Bad_Request, result) : response.send(Http::Code::Ok, result);
      break;
    default:
      result = "Opção inválida";
      response.send(Http::Code::Bad_Request, result);
      break;
    }

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

void BankAPI::debitAccount(const Rest::Request& request, Http::ResponseWriter response) {
    int accountID = std::stoi(request.param(":accountID").as<std::string>());
    double value = std::stod(request.body());

    BankAccount* account = bank.getAccountByID(accountID);

    if(account == nullptr) {
        response.send(Http::Code::Not_Found, "Conta não encontrada");
    } else {
        account->debit(value);
        response.send(Http::Code::Ok, "Débito realizado com sucesso");
    }
}

void BankAPI::transferBetweenAccounts(const Rest::Request& request, Http::ResponseWriter response) {
    json payload = json::parse(request.body());

    BankAccount* originAccount = bank.getAccountByID(payload["from"]);
    BankAccount* destinationAccount = bank.getAccountByID(payload["to"]);
    double amount = payload["amount"].get<double>();

    if(originAccount == nullptr || destinationAccount == nullptr) {
        response.send(Http::Code::Not_Found, "Conta(s) não encontrada(s)");
    } else {
        originAccount->transfer(*destinationAccount, amount);
        response.send(Http::Code::Ok, "Transferência realizada com sucesso");
    }
}

void BankAPI::income(const Rest::Request& request, Http::ResponseWriter response) {
    double rate = std::stod(request.body());
    std::vector<BankAccount*> allAccounts = bank.getAccounts();

    try {
        for(BankAccount* acc : allAccounts) {
            string accountType = bank.getAccountType(acc);
            if("Conta poupança" == accountType) { acc->applyInterestRate(rate); }
        }

        response.send(Http::Code::Ok, "Rendimento aplicado com sucesso");
    } catch(const std::exception& ex) {
        string errorMessage = ex.what(); // in case we need it later
        response.send(Http::Code::Internal_Server_Error, "Erro ao aplicar rendimento");
    }
    
}
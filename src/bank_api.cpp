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

bool BankAPI::contains(string str, string substring) {
   return str.find(substring) != std::string::npos;
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

    if(!payload.contains("id")) {
        response.send(Http::Code::Bad_Request, "Necessário informar ID da conta");
        return;
    } else if(!payload.contains("type")) {
        response.send(Http::Code::Bad_Request, "Necessário informar tipo da conta");
        return;
    } else if((!payload.contains("openingBalance")) && (payload["type"] == 1 || payload["type"] == 2)) {
        response.send(Http::Code::Bad_Request, "Necessário informar saldo inicial");
        return;
    }

    int accountID = payload["id"].get<int>();
    int accountType = payload["type"].get<int>();
    double accountOpeningBalance;
    std::string result;
    
    switch(accountType) {
    case 1:
        accountOpeningBalance = payload["openingBalance"].get<double>();
        result = bank.addAccount(accountID, accountOpeningBalance);
        "Essa conta já existe." == result ? response.send(Http::Code::Bad_Request, result) : response.send(Http::Code::Ok, result);
      break;
    case 2:
        accountOpeningBalance = payload["openingBalance"].get<double>();
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

    string result = bank.consultAccount(accountID);

    if (contains(result, "não existe")) {
        response.send(Http::Code::Not_Found, "Conta não encontrada");
    } else {
        response.send(Http::Code::Ok, result);
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
    json payload = json::parse(request.body());

    if (!payload.contains("credit")) {
        response.send(Http::Code::Bad_Request, "Necessário informar valor a ser creditado");
        return;
    }

    BankAccount* account = bank.getAccountByID(accountID);
    double value = payload["credit"].get<double>();

    if (account == nullptr) {
        response.send(Http::Code::Not_Found, "Conta não encontrada");
        return;
    }

    string result = account->credit(value);
    
    if (contains(result, "novo saldo")) {
        response.send(Http::Code::Ok, result);
    } else {
        response.send(Http::Code::Bad_Request, result);
    }
}

void BankAPI::debitAccount(const Rest::Request& request, Http::ResponseWriter response) {
    int accountID = std::stoi(request.param(":accountID").as<std::string>());
    json payload = json::parse(request.body());

    if(!payload.contains("debit")) {
        response.send(Http::Code::Bad_Request, "Necessário informar valor a ser debitado");
        return;
    }

    double value = payload["debit"].get<double>();
    BankAccount* account = bank.getAccountByID(accountID);

    if (account == nullptr) {
        response.send(Http::Code::Not_Found, "Conta não encontrada");
        return;
    }
    
    string result = account->debit(value);
    
    if (contains(result, "novo saldo")) {
        response.send(Http::Code::Ok, result);
    } else {
        response.send(Http::Code::Bad_Request, result);
    }
}

void BankAPI::transferBetweenAccounts(const Rest::Request& request, Http::ResponseWriter response) {
    json payload = json::parse(request.body());

    BankAccount* originAccount = bank.getAccountByID(payload["from"]);
    BankAccount* destinationAccount = bank.getAccountByID(payload["to"]);
    double amount = payload["amount"].get<double>();

    if (originAccount == nullptr || destinationAccount == nullptr) {
        response.send(Http::Code::Not_Found, "Conta(s) não encontrada(s)");
        return;
    }

    string result = originAccount->transfer(*destinationAccount, amount);

    if (contains(result, "novo saldo")) {
        response.send(Http::Code::Ok, result);
    } else {
        response.send(Http::Code::Bad_Request, result);
    }
}

void BankAPI::income(const Rest::Request& request, Http::ResponseWriter response) {
    json payload = json::parse(request.body());

    if(!payload.contains("rate")) {
        response.send(Http::Code::Bad_Request, "Necessário informar taxa de rendimento");
        return;
    }

    double rate = payload["rate"].get<double>();

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
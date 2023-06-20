#ifndef BANK_API_H
#define BANK_API_H

#include <pistache/endpoint.h>
#include <pistache/http.h>
#include "json.hpp"
#include <pistache/router.h>
#include "../headers/bank.h"
#include "../headers/bank_account.h"
#include "../headers/generic_account.h"
#include "../headers/bonus_account.h"
#include "../headers/savings_account.h"

using namespace Pistache;
using namespace std;
using json = nlohmann::json;

class BankAPI {
    public: 
        explicit BankAPI(Address addr);
        void init(size_t thr = 1);
        void start();
        void shutdown();
    
    private:
        void setupRoutes();
        void createAccount(const Rest::Request& request, Http::ResponseWriter response);
        void consultAccount(const Rest::Request& request, Http::ResponseWriter response);
        void consultAccountBalance(const Rest::Request& request, Http::ResponseWriter response);
        Bank bank;
        Rest::Router router;
        shared_ptr<Http::Endpoint> httpEndpoint;
};

#endif
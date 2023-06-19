#ifndef BANK_API_H
#define BANK_API_H

#include <pistache/endpoint.h>
#include <pistache/http.h>
#include <pistache/router.h>
#include "../headers/bank.h"

using namespace Pistache;
using namespace std;

class BankAPI {
    public: 
        explicit BankAPI(Address addr);
        void init(size_t thr = 1);
        void start();
        void shutdown();
    
    private:
        void setupRoutes();
        void createAccount(const Rest::Request& request, Http::ResponseWriter response);
        Rest::Router router;
        shared_ptr<Http::Endpoint> httpEndpoint;
};

#endif
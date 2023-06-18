#include "../headers/bank_api.h"

using namespace Pistache;

BankAPI::BankAPI(Address addr) : httpEndpoint(std::make_shared<Http::Endpoint>(addr)) {}

void BankAPI::init(size_t thr) {
    auto opts = Http::Endpoint::options().threads(static_cast<int>(thr));
    httpEndpoint->init(opts);
    setupRoutes();
}

void BankAPI::start() {
    httpEndpoint->setHandler(router.handler());
    httpEndpoint->serve();
}

void BankAPI::shutdown() {
    httpEndpoint->shutdown();
}

void BankAPI::setupRoutes() {}
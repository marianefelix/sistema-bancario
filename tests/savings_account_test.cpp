#define CATCH_CONFIG_MAIN
#include "lib/catch.hpp"
#include "../headers/bank.h"

TEST_CASE("Teste do método de criação de conta") {
    SECTION("Criar conta do tipo Poupança") {
        Bank* bank = new Bank();

        // Assert
        REQUIRE(bank->addSavingsAccount(5, 55.55) == "Conta Poupança criada com sucesso!");
    }
}
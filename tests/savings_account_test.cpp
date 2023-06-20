#define CATCH_CONFIG_MAIN
#include "lib/catch.hpp"
#include "../headers/bank.h"
#include "../headers/bank_account.h"
#include "../headers/bonus_account.h"
#include "../headers/savings_account.h"
using namespace std;

Bank* bank = new Bank();

TEST_CASE("Teste do método de criação de conta") {
    SECTION("Criar conta do tipo Poupança com sucesso") {
        // Assert
        REQUIRE(bank->addSavingsAccount(5, 55.55) == "Conta Poupança criada com sucesso!");
    }

    SECTION("Criar conta do tipo Bonus com sucesso") {
        // Assert
        REQUIRE(bank->addBonusAccount(7) == "Conta Bonus criada com sucesso!");
    }

    SECTION("Criar conta do tipo Simples com sucesso") {
        // Assert
        REQUIRE(bank->addAccount(6, 55.55) == "Conta Simples criada com sucesso!");
    }
    SECTION("Criar conta do tipo Poupança sem sucesso") {
        // Assert
        REQUIRE(bank->addSavingsAccount(5, 55.55) == "Essa conta já existe.");
    }

    SECTION("Criar conta do tipo Bonus sem sucesso") {
        // Assert
        REQUIRE(bank->addBonusAccount(7) == "Essa conta já existe.");
    }

    SECTION("Criar conta do tipo Simples sem sucesso") {
        // Assert
        REQUIRE(bank->addAccount(6, 55.55) == "Essa conta já existe.");
    }
}

TEST_CASE("Teste do método de crédito em conta") {
    SECTION("Creditar conta do tipo Simples com sucesso") {
        // Assert
        BankAccount* getAccount = bank->getAccountByID(6);

        double value = 35.25;
        getAccount->credit(value);

        REQUIRE(getAccount->getBalance() == 90.80);
    }

    SECTION("Creditar conta do tipo Simples utilizando valor negativo") {
        // Assert
        BankAccount* getAccount = bank->getAccountByID(6);

        double value = -5;
        getAccount->credit(value);

        REQUIRE(getAccount->getBalance() == 85.80);
    }

    SECTION("Creditar conta do tipo Poupança com sucesso") {
        // Assert
        BankAccount* getAccount = bank->getAccountByID(5);

        double value = 0.1;
        SavingsAccount* savingsAccount = dynamic_cast<SavingsAccount*>(getAccount);
        savingsAccount->credit(value);
        
        REQUIRE(savingsAccount->getBalance() == 55.65);
    }

    SECTION("Creditar conta do tipo Poupança utilizando valor negativo") {
        // Assert
        BankAccount* getAccount = bank->getAccountByID(5);

        double value = -1;
        SavingsAccount* savingsAccount = dynamic_cast<SavingsAccount*>(getAccount);
        savingsAccount->credit(value);
        REQUIRE(savingsAccount->getBalance() == 54.65);
    }

    SECTION("Creditar conta do tipo Bonus, sem adição de bonus, com sucesso") {
        // Assert
        BankAccount* getAccount = bank->getAccountByID(7);

        double value = 5.55;
        
        BonusAccount* bonusAccount = dynamic_cast<BonusAccount*>(getAccount);
        bonusAccount->credit(value);

        bonusAccount->addBonusCredit(value);

        REQUIRE(bonusAccount->getBalance() == 5.55);
        REQUIRE(bonusAccount->getScore() == 10);
    }

    SECTION("Creditar conta do tipo Bonus, sem adição de bonus, e com valor negativo") {
        // Assert
        BankAccount* getAccount = bank->getAccountByID(7);

        double value = -2;
        
        BonusAccount* bonusAccount = dynamic_cast<BonusAccount*>(getAccount);
        bonusAccount->credit(value);

        bonusAccount->addBonusCredit(value);

        REQUIRE(bonusAccount->getBalance() == 3.55);
        REQUIRE(bonusAccount->getScore() == 10);
    }

    SECTION("Creditar conta do tipo Bonus, com adição de bonus, com sucesso") {
        // Assert
        BankAccount* getAccount = bank->getAccountByID(7);

        double value = 200;
        
        BonusAccount* bonusAccount = dynamic_cast<BonusAccount*>(getAccount);
        bonusAccount->credit(value);

        bonusAccount->addBonusCredit(value);

        REQUIRE(bonusAccount->getBalance() == 203.55);
        REQUIRE(bonusAccount->getScore() == 12);
    }
}

TEST_CASE("Teste do método de débito em conta") {
    SECTION("Debitar conta do tipo Simples com sucesso") {
        // Assert
        BankAccount* getAccount = bank->getAccountByID(6);

        double value = 35.25;
        getAccount->debit(value);

        REQUIRE(getAccount->getBalance() == 50.55);
    }

    SECTION("Debitar conta do tipo Simples utilizando valor negativo") {
        // Assert
        BankAccount* getAccount = bank->getAccountByID(6);

        double value = -5;
        getAccount->debit(value);

        REQUIRE(getAccount->getBalance() == 55.55);
    }

    SECTION("Debitar conta do tipo Simples deixando saldo negativo") {
        // Assert
        BankAccount* getAccount = bank->getAccountByID(6);

        double value = 155.55;
        getAccount->debit(value);

        REQUIRE(getAccount->getBalance() == -100);
    }

    SECTION("Debitar conta do tipo Poupança com sucesso") {
        // Assert
        BankAccount* getAccount = bank->getAccountByID(5);

        double value = 2;
        SavingsAccount* savingsAccount = dynamic_cast<SavingsAccount*>(getAccount);
        savingsAccount->debit(value);

        REQUIRE(savingsAccount->getBalance() == 52.65);
    }

    SECTION("Debitar conta do tipo Poupança utilizando valor negativo") {
        // Assert
        BankAccount* getAccount = bank->getAccountByID(5);

        double value = -1;
        SavingsAccount* savingsAccount = dynamic_cast<SavingsAccount*>(getAccount);
        savingsAccount->debit(value);

        REQUIRE(savingsAccount->getBalance() == 53.65);
    }

    SECTION("Debitar conta do tipo Poupança deixando saldo negativo") {
        // Assert
        BankAccount* getAccount = bank->getAccountByID(5);

        double value = 300;
        SavingsAccount* savingsAccount = dynamic_cast<SavingsAccount*>(getAccount);
        savingsAccount->debit(value);

        REQUIRE(savingsAccount->getBalance() == -100);
    }

    SECTION("Debitar conta do tipo Bonus com sucesso") {
        // Assert
        BankAccount* getAccount = bank->getAccountByID(7);

        double value = 3.55;
        BonusAccount* bonusAccount = dynamic_cast<BonusAccount*>(getAccount);
        bonusAccount->debit(value);

        REQUIRE(bonusAccount->getBalance() == 200);
    }

    SECTION("Debitar conta do tipo Bonus utilizando valor negativo") {
        // Assert
        BankAccount* getAccount = bank->getAccountByID(7);

        double value = -2;
        BonusAccount* bonusAccount = dynamic_cast<BonusAccount*>(getAccount);
        bonusAccount->debit(value);

        REQUIRE(bonusAccount->getBalance() == 202);
    }

    SECTION("Debitar conta do tipo Bonus deixando saldo negativo") {
        // Assert
        BankAccount* getAccount = bank->getAccountByID(7);

        double value = 302;
        BonusAccount* bonusAccount = dynamic_cast<BonusAccount*>(getAccount);
        bonusAccount->debit(value);

        REQUIRE(bonusAccount->getBalance() == -100);
    }
}
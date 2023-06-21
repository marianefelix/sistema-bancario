#define CATCH_CONFIG_MAIN
#include "lib/catch.hpp"
#include "../headers/bank.h"
#include "../headers/bank_account.h"
#include "../headers/bonus_account.h"
#include "../headers/savings_account.h"
#include "../headers/generic_account.h"
using namespace std;

Bank* bank = new Bank();

//
// TEST: CREATE ACCOUNTS - GENERIC, SAVINGS, BONUS.
//
TEST_CASE("Test account creation method") {
    SECTION("Create Savings account successfully") {
        REQUIRE(bank->addSavingsAccount(5, 55.55) == "Conta Poupança criada com sucesso!");
    }

    SECTION("Create Bonus account successfully") {
        REQUIRE(bank->addBonusAccount(7) == "Conta Bonus criada com sucesso!");
    }

    SECTION("Create Generic account successfully") {
        REQUIRE(bank->addAccount(6, 55.55) == "Conta Simples criada com sucesso!");
    }

    SECTION("Create Savings account without success") {
        REQUIRE(bank->addSavingsAccount(5, 55.55) == "Essa conta já existe.");
    }

    SECTION("Create Bonus account without success") {
        REQUIRE(bank->addBonusAccount(7) == "Essa conta já existe.");
    }

    SECTION("Create Generic account without success") {
        REQUIRE(bank->addAccount(6, 55.55) == "Essa conta já existe.");
    }
}

//
// TEST: CONSULT ACCOUNT.
//
TEST_CASE("Test account query method") {
    SECTION("Query savings account successfully") {
        REQUIRE(bank->consultAccount(5) == "Tipo: Conta poupança  |  Saldo: 55.550000  |  Número: 5");
    }

    SECTION("Query generic account successfully") {
        REQUIRE(bank->consultAccount(7) == "Tipo: Conta bônus  |  Saldo: 0.000000  |  Número: 7  |  Bônus: 10.000000");
    }

    SECTION("Query bonus account successfully") {
        REQUIRE(bank->consultAccount(6) == "Tipo: Conta simples  |  Saldo: 55.550000  |  Número: 6");
    }

    SECTION("Query account without success") {
        REQUIRE(bank->consultAccount(22) == "Essa conta não existe");
    }
}

//
// TEST: CONSULT BALANCE.
//
TEST_CASE("Test balance query method") {
    SECTION("Query Savings account balance successfully") {
        REQUIRE(bank->consultAccountBalance(5) == "O seu saldo é: 55.550000");
    }

    SECTION("Query Generic account balance successfully") {
        REQUIRE(bank->consultAccountBalance(6) == "O seu saldo é: 55.550000");
    }

    SECTION("Query Bonus account balance successfully") {
        REQUIRE(bank->consultAccountBalance(7) == "O seu saldo é: 0.000000");
    }
    
    SECTION("Query balance without success") {
        REQUIRE(bank->consultAccountBalance(22) == "Essa conta não existe");
    }
}

//
// TEST: CREDIT ACCOUNT.
//
TEST_CASE("Test account credit method") {
    SECTION("Credit Simple account successfully") {
        BankAccount* getAccount = bank->getAccountByID(6);

        double value = 35.25;

        REQUIRE(getAccount->credit(value) == "Seu novo saldo é: 90.800000");
    }

    SECTION("Credit Simple account using negative amount") {
        BankAccount* getAccount = bank->getAccountByID(6);

        double value = -5;

        REQUIRE(getAccount->credit(value) == "Digite um valor maior ou igual a 0.");
    }

    SECTION("Credit savings account successfully") {
        BankAccount* getAccount = bank->getAccountByID(5);

        double value = 0.1;
        SavingsAccount* savingsAccount = dynamic_cast<SavingsAccount*>(getAccount);
        
        REQUIRE(savingsAccount->credit(value) == "Seu novo saldo é: 55.650000");
    }

    SECTION("Credit savings account using negative amount") {
        BankAccount* getAccount = bank->getAccountByID(5);

        double value = -1;
        SavingsAccount* savingsAccount = dynamic_cast<SavingsAccount*>(getAccount);

        REQUIRE(savingsAccount->credit(value) == "Digite um valor maior ou igual a 0.");
    }

    SECTION("Credit Bonus account, no bonus added, successfully") {
        BankAccount* getAccount = bank->getAccountByID(7);

        double value = 5.55;
        
        BonusAccount* bonusAccount = dynamic_cast<BonusAccount*>(getAccount);

        REQUIRE(bonusAccount->credit(value) == "Seu novo saldo é: 5.550000  |  Seu bonus atualizado: 10.000000");
    }

    SECTION("Credit Bonus account, no bonus added, using negative amount") {
        BankAccount* getAccount = bank->getAccountByID(7);

        double value = -2;
        
        BonusAccount* bonusAccount = dynamic_cast<BonusAccount*>(getAccount);

        REQUIRE(bonusAccount->credit(value) == "Digite um valor maior ou igual a 0.");
    }

    SECTION("Credit Bonus account, with bonus added, successfully") {
        BankAccount* getAccount = bank->getAccountByID(7);

        double value = 200;
        
        BonusAccount* bonusAccount = dynamic_cast<BonusAccount*>(getAccount);

        REQUIRE(bonusAccount->credit(value) == "Seu novo saldo é: 205.550000  |  Seu bonus atualizado: 12.000000");
    }
}

//
// TEST: DEBIT ACCOUNT.
//
TEST_CASE("Test account debit method") {
    SECTION("Debit Simple account successfully") {
        BankAccount* getAccount = bank->getAccountByID(6);

        double value = 35.25;
        getAccount->debit(value);

        REQUIRE(getAccount->getBalance() == 55.55);
    }

    SECTION("Debit Simple account using negative amount") {
        BankAccount* getAccount = bank->getAccountByID(6);

        double value = -5;

        REQUIRE(getAccount->debit(value) == "Digite um valor maior ou igual a 0.");
    }

    SECTION("Debit Simple account leaving negative balance") {
        BankAccount* getAccount = bank->getAccountByID(6);

        double value = 155.55;

        REQUIRE(getAccount->debit(value) == "Não há saldo suficiente para debitar.");
    }

    SECTION("Debit Savings account successfully") {
        BankAccount* getAccount = bank->getAccountByID(5);

        double value = 2;
        SavingsAccount* savingsAccount = dynamic_cast<SavingsAccount*>(getAccount);

        REQUIRE(savingsAccount->debit(value) == "Seu novo saldo é: 53.650000");
    }

    SECTION("Debit Savings account using negative amount") {
        BankAccount* getAccount = bank->getAccountByID(5);

        double value = -1;
        SavingsAccount* savingsAccount = dynamic_cast<SavingsAccount*>(getAccount);

        REQUIRE(savingsAccount->debit(value) == "Digite um valor maior ou igual a 0.");
    }

    SECTION("Debit Savings account leaving negative balance") {
        BankAccount* getAccount = bank->getAccountByID(5);

        double value = 300;
        SavingsAccount* savingsAccount = dynamic_cast<SavingsAccount*>(getAccount);

        REQUIRE(savingsAccount->debit(value) == "Não há saldo suficiente para debitar.");
    }

    SECTION("Debit Bonus account successfully") {
        BankAccount* getAccount = bank->getAccountByID(7);

        double value = 3.55;
        BonusAccount* bonusAccount = dynamic_cast<BonusAccount*>(getAccount);

        REQUIRE(bonusAccount->debit(value) == "Seu novo saldo é: 202.000000");
    }

    SECTION("Debit Bonus account using negative amount") {
        BankAccount* getAccount = bank->getAccountByID(7);

        double value = -2;
        BonusAccount* bonusAccount = dynamic_cast<BonusAccount*>(getAccount);

        REQUIRE(bonusAccount->debit(value) == "Digite um valor maior ou igual a 0.");
    }

    SECTION("Debit Bonus account leaving negative balance") {
        BankAccount* getAccount = bank->getAccountByID(7);

        double value = 302;
        BonusAccount* bonusAccount = dynamic_cast<BonusAccount*>(getAccount);

        REQUIRE(bonusAccount->debit(value) == "Não há saldo suficiente para debitar.");
    }
}

//
// TEST: INTER-ACCOUNT TRANSFER.
//
TEST_CASE("Testing the inter-account transfer method") {
    SECTION("Transfer Simple account to Savings account successfully") {
        bank->addSavingsAccount(50, 500);
        BankAccount* getSavingsAccount = bank->getAccountByID(50);

        bank->addAccount(75, 500);
        BankAccount* getGenericAccount = bank->getAccountByID(75);

        REQUIRE(getGenericAccount->transfer(*getSavingsAccount, 20.0) == "Transferência realizada com sucesso! Seu novo saldo é: 480.000000");
    }

    SECTION("Transfer Simple account to Bonus account successfully") {
        bank->addBonusAccount(70);
        BankAccount* getBonusAccount = bank->getAccountByID(70);
        getBonusAccount->credit(500);

        BankAccount* getGenericAccount = bank->getAccountByID(75);

        REQUIRE(getGenericAccount->transfer(*getBonusAccount, 20.0) == "Transferência realizada com sucesso! Seu novo saldo é: 460.000000");
    }
    
    SECTION("Transfer Savings account to Simple account successfully") {
        BankAccount* getSavingsAccount = bank->getAccountByID(50);
        BankAccount* getGenericAccount = bank->getAccountByID(75);

        REQUIRE(getSavingsAccount->transfer(*getGenericAccount, 20.0) == "Transferência realizada com sucesso! Seu novo saldo é: 500.000000");
    }
    
    SECTION("Transfer Savings account to Bonus account successfully") {
        BankAccount* getSavingsAccount = bank->getAccountByID(50);
        BankAccount* getBonusAccount = bank->getAccountByID(70);

        REQUIRE(getSavingsAccount->transfer(*getBonusAccount, 20.0) == "Transferência realizada com sucesso! Seu novo saldo é: 480.000000");
    }
    
    SECTION("Transfer Bonus account to Simple account successfully") {
        BankAccount* getBonusAccount = bank->getAccountByID(70);
        BankAccount* getGenericAccount = bank->getAccountByID(75);

        REQUIRE(getBonusAccount->transfer(*getGenericAccount, 20.0) == "Transferência realizada com sucesso! Seu novo saldo é: 520.000000  |  Seu bonus atualizado: 15.000000");
    }
    
    SECTION("Transfer Bonus account to Savings account successfully") {
        BankAccount* getSavingsAccount = bank->getAccountByID(50);
        BankAccount* getBonusAccount = bank->getAccountByID(70);

        REQUIRE(getBonusAccount->transfer(*getSavingsAccount, 200) == "Transferência realizada com sucesso! Seu novo saldo é: 320.000000  |  Seu bonus atualizado: 16.000000");
    }

    SECTION("Transfer Simple account to Bonus account unsuccessful since negative value") {
        BankAccount* getBonusAccount = bank->getAccountByID(70);
        BankAccount* getGenericAccount = bank->getAccountByID(75);

        REQUIRE(getGenericAccount->transfer(*getBonusAccount, -20) == "Digite um valor maior ou igual a 0.");
    }
    
    SECTION("Transfer Savings account to Bonus account unsuccessful since negative value") {
        BankAccount* getSavingsAccount = bank->getAccountByID(50);
        BankAccount* getGenericAccount = bank->getAccountByID(75);

        REQUIRE(getSavingsAccount->transfer(*getGenericAccount, -20) == "Digite um valor maior ou igual a 0.");
    }
    
    SECTION("Transfer Bonus account to Savings account unsuccessful since negative value") {
        BankAccount* getSavingsAccount = bank->getAccountByID(50);
        BankAccount* getBonusAccount = bank->getAccountByID(70);

        REQUIRE(getBonusAccount->transfer(*getSavingsAccount, -20) == "Digite um valor maior ou igual a 0.");
    }

    SECTION("Transfer Simple account to Bonus account unsuccessfully as the balance will become negative if you transfer") {
        BankAccount* getBonusAccount = bank->getAccountByID(70);
        BankAccount* getGenericAccount = bank->getAccountByID(75);

        REQUIRE(getGenericAccount->transfer(*getBonusAccount, 10000) == "Não há saldo suficiente para transferir.");
    }
    
    SECTION("Transfer Savings account to Bonus account unsuccessfully as the balance will become negative if you transfer") {
        BankAccount* getSavingsAccount = bank->getAccountByID(50);
        BankAccount* getGenericAccount = bank->getAccountByID(75);

        REQUIRE(getSavingsAccount->transfer(*getGenericAccount, 10000) == "Não há saldo suficiente para transferir.");
    }
    
    SECTION("Transfer Bonus account to Savings account unsuccessfully as the balance will become negative if you transfer") {
        BankAccount* getSavingsAccount = bank->getAccountByID(50);
        BankAccount* getBonusAccount = bank->getAccountByID(70);
        
        REQUIRE(getBonusAccount->transfer(*getSavingsAccount, 10000) == "Não há saldo suficiente para transferir.");
    }
}

//
// TEST: YIELD INTEREST.
//
TEST_CASE("Testing the interest yielding method in savings accounts") {
    SECTION("Earning interest with a savings account - success") {
        BankAccount* getSavingsAccount = bank->getAccountByID(50);
        double value = 5.0;

        REQUIRE(getSavingsAccount->applyInterestRate(value) == "Saldo atualizado: 714.000000");
    }

    SECTION("Attempting interest income with simple account type") {
        BankAccount* getGenericAccount = bank->getAccountByID(75);

        double value = 5.0;

        REQUIRE(getGenericAccount->applyInterestRate(value) == "Essa conta não é uma Conta Poupança.");
    }

    SECTION("Attempting interest income with bonus account type") {
        BankAccount* getBonusAccount = bank->getAccountByID(70);

        double value = 5.0;

        REQUIRE(getBonusAccount->applyInterestRate(value) == "Essa conta não é uma Conta Poupança.");
    }
}
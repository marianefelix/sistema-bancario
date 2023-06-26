.DEFAULT_GOAL := all

objects/bank_account.o: ../src/bank_account.cpp ../headers/bank_account.h
	g++ ../src/bank_account.cpp -Iheaders -Wall -ansi -pedantic -std=c++17 -g -c -o objects/bank_account.o

objects/generic_account.o: ../src/generic_account.cpp ../headers/generic_account.h objects/bank_account.o
	g++ ../src/generic_account.cpp -Iheaders -Wall -ansi -pedantic -std=c++17 -g -c -o objects/generic_account.o

objects/savings_account.o: ../src/savings_account.cpp ../headers/savings_account.h objects/bank_account.o
	g++ ../src/savings_account.cpp -Iheaders -Wall -ansi -pedantic -std=c++17 -g -c -o objects/savings_account.o

objects/bonus_account.o: ../src/bonus_account.cpp ../headers/bonus_account.h objects/bank_account.o
	g++ ../src/bonus_account.cpp -Iheaders -Wall -ansi -pedantic -std=c++17 -g -c -o objects/bonus_account.o

objects/bank.o: ../src/bank.cpp ../headers/bank.h objects/bank_account.o objects/generic_account.o objects/savings_account.o objects/bonus_account.o
	g++ ../src/bank.cpp -Iheaders -Wall -ansi -pedantic -std=c++17 -g -c -o objects/bank.o

objects/test_main.o: test_main.cpp objects/bank.o
	g++ test_main.cpp -Iheaders -Wall -ansi -pedantic -std=c++17 -g -c -o objects/test_main.o

testapp: objects/test_main.o objects/bank.o objects/bank_account.o objects/generic_account.o objects/savings_account.o objects/bonus_account.o
	g++ objects/*.o -Iheaders -Wall -ansi -pedantic -std=c++17 -g -o testapp

# cria a pasta objects
create_objects:
	mkdir objects

all: create_objects testapp

run:
	./testapp
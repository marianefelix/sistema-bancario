.DEFAULT_GOAL := all

objects/bank_account.o: src/bank_account.cpp headers/bank_account.h
	g++ src/bank_account.cpp -Iheaders -Wall -ansi -pedantic -std=c++11 -g -c -o objects/bank_account.o

objects/generic_account.o: src/generic_account.cpp headers/generic_account.h objects/bank_account.o
	g++ src/generic_account.cpp -Iheaders -Wall -ansi -pedantic -std=c++11 -g -c -o objects/generic_account.o

objects/savings_account.o: src/savings_account.cpp headers/savings_account.h objects/bank_account.o
	g++ src/savings_account.cpp -Iheaders -Wall -ansi -pedantic -std=c++11 -g -c -o objects/savings_account.o

objects/bonus_account.o: src/bonus_account.cpp headers/bonus_account.h objects/bank_account.o
	g++ src/bonus_account.cpp -Iheaders -Wall -ansi -pedantic -std=c++11 -g -c -o objects/bonus_account.o

objects/bank.o: src/bank.cpp headers/bank.h objects/bank_account.o objects/generic_account.o objects/savings_account.o objects/bonus_account.o
	g++ src/bank.cpp -Iheaders -Wall -ansi -pedantic -std=c++11 -g -c -o objects/bank.o

objects/navigation_menu.o: src/navigation_menu.cpp headers/navigation_menu.h objects/bank_account.o objects/generic_account.o objects/savings_account.o
	g++ src/navigation_menu.cpp -Iheaders -Wall -ansi -pedantic -std=c++11 -g -c -o objects/navigation_menu.o

objects/bank_api.o: src/bank_api.cpp headers/bank_api.h headers/bank.h headers/bank_account.h headers/generic_account.h headers/savings_account.h headers/bonus_account.h
	g++ src/bank_api.cpp -Iheaders -Wall -ansi -pedantic -std=c++11 -g -c -o objects/bank_api.o

objects/main.o: src/main.cpp objects/navigation_menu.o objects/bank.o objects/bank_api.o
	g++ src/main.cpp -Iheaders -Wall -ansi -pedantic -std=c++11 -g -c -o objects/main.o

bankapp: objects/main.o objects/navigation_menu.o objects/bank.o objects/bank_account.o objects/generic_account.o objects/savings_account.o objects/bonus_account.o objects/bank_api.o
	g++ objects/*.o -Iheaders -Wall -ansi -pedantic -std=c++11 -g -o bankapp

# cria a pasta objects
create_objects:
	mkdir objects

all: create_objects bankapp

run:
	./bankapp
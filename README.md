# Banking system
This system simulates a simple bank. The main purpose of this repository is to practice studies in configuration and change management.

## Compile and run
From the root of the project

`$ g++ -std=c++11 -Wall -Wextra -pedantic -g -c bank_account.cpp bank.cpp navigation_menu.cpp main.cpp`

`$ g++ -o bank bank_account.o bank.o navigation_menu.o main.o`

and then

`$ ./bank`
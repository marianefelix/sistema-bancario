# Banking system
This system simulates a simple bank. The main purpose of this repository is to practice studies in configuration and change management.

## Compile and run
From the root of the project

`$ g++ -std=c++11 -Wall -Wextra -c src/bank_account.cpp src/bonus_account.cpp src/bank.cpp src/navigation_menu.cpp src/main.cpp`

`$ g++ -o bankapp bank_account.o bonus_account.o bank.o navigation_menu.o main.o`

and then

`$ ./bankapp`
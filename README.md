# Banking system
This system simulates a simple bank. The main purpose of this repository is to practice studies in configuration and change management.

<br>

# Project informations
- Workflow: **`GitFlow`**

- We use a commit pattern that can be found here: [**Conventional Commits**](https://www.conventionalcommits.org/en/v1.0.0/)

- Here is an image of the code tree built by **GitKraken**:

<br>

![Tree head](./images/photo1.jpeg)

![Tree body 3](./images/photo2.jpeg)

![Tree body 2](./images/photo3.jpeg)

![Tree body 1](./images/photo4.jpeg)

![Tree root](./images/photo5.jpeg)

<br>
<br>

# APP
After implementing the frontend communication with the backend through a Rest API, we had the need to ninch the operating system to Ubuntu due to the framework we used, Pistache, which requires its execution to be done through this OS. Therefore, the banking system must run on this OS, either on the machine itself or using a virtual machine. Teste

<br>

### **Compile and run with Makefile**
To run the banking system, you only need to follow these steps:
<!-- - Be using Ubuntu operating system -->
- Be in the project root folder
- In the terminal, run the command:
> $ `make`
- In the terminal, run the command:
> $ `./bankapp`
- The application will be running.

<br>

### **Compile and run without using Makefile**
<!-- If you are using the Ubuntu operating system, go to the project directory. -->

From the root of the project, use these commands:

> $ `g++ -std=c++17 -Wall -Wextra -c src/bank_account.cpp src/savings_account.cpp src/generic_account.cpp src/bonus_account.cpp  src/bank.cpp src/navigation_menu.cpp src/main.cpp src/bank_api.cpp`

> $ `g++ -o bankapp bank_account.o savings_account.o generic_account.o bonus_account.o  bank.o navigation_menu.o main.o bank_api.o -lpistache`

and then

> $ `./bankapp`

<br>
<br>

# TESTING
The tests implemented were unit tests for the banking operations - without calls to the REST API layer. Therefore, because it does not use API communication, there is no need to run the tests on an Ubuntu operating system.

<br>


### **Compile and run with Makefile**
So if your operating system is **`Windows`**, you must have MinGW installed.
If not, please install it.
If you do, follow the next steps to run the tests:
- Access the "tests" folder that is present in the project root
> $ `cd .\tests\`
- In the terminal, run the command:
> $ `mingw32-make`
- In the terminal, run the command:
> $ `./testapp`
- The tests will be executed.

<br>

If your operating system is **`Ubuntu`**, you only need to follow these steps:
- Access the "tests" folder that is present in the project root
> $ `cd .\tests\`
- In the terminal, run the command:
> $ `make`
- In the terminal, run the command:
> $ `./testapp`
- The tests will be executed.

<br>

### **Compile and run without using Makefile**
From the root of the project

> $ `g++ -std=c++11 -Wall -Wextra -c ../src/bank_account.cpp ../src/savings_account.cpp ../src/generic_account.cpp ../src/bonus_account.cpp ../src/bank.cpp test_main.cpp`

> $ `g++ -o testapp bank_account.o savings_account.o generic_account.o bonus_account.o bank.o test_main.o`

and then

> $ `./testapp`
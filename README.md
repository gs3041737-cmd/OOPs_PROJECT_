# OOPs_PROJECT_
# Banking Management System (C++)

A menu-driven **Banking Management System** developed in C++ using Object-Oriented Programming (OOP) concepts. The program allows users to create and manage customer accounts, search account records, and perform basic banking transactions. Account records are stored in a binary data file so that they remain available when the program is run again.

## Table of Contents

- [Project Overview](#project-overview)
- [Objectives](#objectives)
- [Features](#features)
- [OOP Concepts Used](#oop-concepts-used)
- [Project Structure](#project-structure)
- [How the System Works](#how-the-system-works)
- [Data Storage](#data-storage)
- [Requirements](#requirements)
- [How to Compile and Run](#how-to-compile-and-run)
- [Validation and Error Handling](#validation-and-error-handling)
- [Limitations](#limitations)
- [Future Scope](#future-scope)
- [Conclusion](#conclusion)

## Project Overview

The Banking Management System is a console-based C++ application that manages basic customer account information. Through a menu, the user can create a new account, view all accounts, search for a particular account, deposit money, withdraw money, modify account details, and delete an account.

The project is divided into multiple source files. The `Account` class stores account data and provides member functions to perform account-related operations. File handling is used to save and update account records in `bank.dat`.

## Objectives

- To develop a basic banking application using C++.
- To apply classes, objects, encapsulation, and member functions.
- To perform account creation, searching, modification, and deletion.
- To implement deposit and withdrawal operations.
- To store account records using file handling.
- To practise modular programming by separating the program into multiple files.
- To validate user input and handle common errors.

## Features

1. **Create New Account:** Accepts an account number, customer name, account type, and initial deposit.
2. **Display All Accounts:** Displays the saved account records in a tabular format.
3. **Search Account:** Finds an account using its account number.
4. **Deposit Amount:** Adds a valid deposit amount to an account balance.
5. **Withdraw Amount:** Deducts money when the amount is valid and sufficient balance is available.
6. **Modify Account:** Updates the customer name and account type.
7. **Delete Account:** Removes the selected account record.
8. **Exit:** Closes the menu-driven program.

## OOP Concepts Used

### 1. Class

The project defines a class named `Account`. It groups the data and functions related to a bank account into one unit.

### 2. Object

Objects of the `Account` class are created to hold and process individual account records. For example, the program creates an `Account` object while reading or writing account data.

### 3. Encapsulation

The data members `accountNumber`, `name`, `accountType`, and `balance` are declared under the `private` access specifier. Public member functions provide controlled operations on this data.

### 4. Member Functions

Functions such as `createAccount()`, `displayAccount()`, `deposit()`, `withdraw()`, `modifyAccount()`, and `showDetails()` define the operations that can be performed on an account.

**Note:** The current implementation demonstrates classes, objects, and encapsulation. It does not implement inheritance or runtime polymorphism.

## Project Structure

| File | Description |
|---|---|
| `bank.h` | Declares the `Account` class and the functions used across the project. |
| `main.cpp` | Contains the main menu and directs the user's selection to the relevant function. |
| `account.cpp` | Defines account-related member functions and account creation, modification, and deletion operations. |
| `display.cpp` | Contains functions to display all accounts and search for an account. |
| `transactions.cpp` | Contains the deposit and withdrawal operations. |
| `codeinc++.cpp` | Contains a consolidated, single-file version of the program. It is separate from the multi-file build described below. |
| `bank.dat` | Binary data file created by the program at runtime to store account records. |

## How the System Works

1. The program starts from `main()` and displays the banking menu.
2. The user selects an operation by entering a menu number.
3. The selected function is called through the `switch` statement.
4. Account information is handled through objects of the `Account` class.
5. The program reads or updates account records in the binary file `bank.dat`.
6. The menu continues to appear until the user selects the Exit option.

## Data Storage

The project uses C++ file handling with binary file streams:

- `ifstream` is used to read account records.
- `ofstream` is used to create or append account records.
- `fstream` is used when an existing record must be read and updated.
- `bank.dat` stores the account records.
- A temporary file named `temp.dat` is used during account deletion.

The data file is created in the program's working directory when an account is saved.

## Requirements

### Software Requirements

- C++ compiler (such as GCC/G++).
- Visual Studio Code or another C++ development environment.
- C++ standard library.

### Hardware Requirements

- A computer capable of running a C++ compiler.
- Keyboard and display.

## How to Compile and Run

Open a terminal in the project folder and compile the **multi-file version** with:

```bash
g++ -std=c++11 main.cpp account.cpp display.cpp transactions.cpp -o banking
```

Run on Windows:

```bash
banking.exe
```

Run on Linux or macOS:

```bash
./banking
```

**Important:** Do not include `codeinc++.cpp` in the compile command above. It is a consolidated version containing its own `main()` and repeated definitions. The command uses the separate source files that make up the multi-file project.

## Validation and Error Handling

The program includes checks for common invalid inputs and account operations, including:

- Invalid account numbers and menu choices.
- Empty customer names or account types during account creation.
- Negative, zero, or non-finite deposit and withdrawal amounts.
- Duplicate account numbers during account creation.
- Withdrawal amounts greater than the available balance.
- Attempts to access accounts that do not exist.
- Errors when opening or updating data files.

## Limitations

- The application is console-based and does not have a graphical user interface.
- It does not include user login, passwords, or role-based access.
- Account data is stored in a local binary file and is not encrypted.
- It does not maintain a separate transaction history or generate statements.
- It is an educational project and is not intended for real banking use.

## Future Scope

The project can be extended by adding:

- Secure user authentication.
- A transaction history with date and time.
- Mini statements and account reports.
- Improved data protection and secure storage.
- A graphical user interface.
- Database connectivity for managing larger sets of records.

## Conclusion

The Banking Management System demonstrates how C++ can be used to develop a menu-driven application for basic banking operations. It provides practice in classes, objects, encapsulation, member functions, file handling, input validation, and modular programming. The project also shows how account records can be stored and updated using binary files.

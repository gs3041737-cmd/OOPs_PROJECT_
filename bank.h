
#ifndef BANK_H
#define BANK_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits>
#include <cstring>
#include <cstdio>
#include <string>
#include <cmath>

using namespace std;

extern const char FILE_NAME[];

// Account class
class Account {
private:
    int accountNumber;
    char name[50];
    char accountType[20];
    double balance;

public:
    Account();

    bool createAccount();
    void displayAccount() const;
    bool modifyAccount();

    void deposit(double amount);
    bool withdraw(double amount);
    bool depositMoney(double amount);

    int getAccountNumber() const;
    void showDetails() const;
};

// Account operations
void createNewAccount();
void modifyAccount();
void deleteAccount();
bool accountExists(int number);

// Display operations
void displayAllAccounts();
void searchAccount();

// Transaction operations
void depositMoney();
void withdrawMoney();

#endif

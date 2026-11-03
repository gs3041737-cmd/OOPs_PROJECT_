
#include "bank.h"

// Deposit money
void depositMoney() {
    int number;
    double amount;

    cout << "Enter Account Number: ";

    if (!(cin >> number)) {
        cout << "Invalid account number!\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    cout << "Enter Deposit Amount: ";

    if (!(cin >> amount) || amount <= 0 || !isfinite(amount)) {
        cout << "Invalid deposit amount!\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    fstream file(FILE_NAME, ios::binary | ios::in | ios::out);
    Account account;

    if (!file) {
        cout << "No account records found.\n";
        return;
    }

    while (file.read(reinterpret_cast<char*>(&account),
                     sizeof(account))) {

        if (account.getAccountNumber() == number) {

            if (account.depositMoney(amount)) {
                file.seekp(-static_cast<streamoff>(sizeof(account)),
                           ios::cur);

                file.write(reinterpret_cast<char*>(&account),
                           sizeof(account));

                cout << (file ? "Account updated in file.\n"
                              : "Error updating file!\n");
            }

            return;
        }
    }

    cout << "Account not found!\n";
}

// Withdraw money
void withdrawMoney() {
    int number;
    double amount;

    cout << "Enter Account Number: ";

    if (!(cin >> number)) {
        cout << "Invalid account number!\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    cout << "Enter Withdrawal Amount: ";

    if (!(cin >> amount) || amount <= 0 || !isfinite(amount)) {
        cout << "Invalid withdrawal amount!\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    fstream file(FILE_NAME, ios::binary | ios::in | ios::out);
    Account account;

    if (!file) {
        cout << "No account records found.\n";
        return;
    }

    while (file.read(reinterpret_cast<char*>(&account),
                     sizeof(account))) {

        if (account.getAccountNumber() == number) {

            if (account.withdraw(amount)) {
                file.seekp(-static_cast<streamoff>(sizeof(account)),
                           ios::cur);

                file.write(reinterpret_cast<char*>(&account),
                           sizeof(account));

                cout << (file ? "Account updated in file.\n"
                              : "Error updating file!\n");
            }

            return;
        }
    }

    cout << "Account not found!\n";
}

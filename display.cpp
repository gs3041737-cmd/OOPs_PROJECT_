
#include "bank.h"

// Display all accounts
void displayAllAccounts() {
    ifstream file(FILE_NAME, ios::binary);
    Account account;
    bool found = false;

    if (!file) {
        cout << "No account records found.\n";
        return;
    }

    cout << "\n"
         << left << setw(15) << "Account No."
         << setw(25) << "Customer Name"
         << setw(15) << "Account Type"
         << "Balance\n";

    cout << string(70, '-') << '\n';

    while (file.read(reinterpret_cast<char*>(&account),
                     sizeof(account))) {

        account.displayAccount();
        found = true;
    }

    if (!found)
        cout << "No accounts available.\n";
}

// Search account
void searchAccount() {
    int number;

    cout << "Enter Account Number to Search: ";

    if (!(cin >> number)) {
        cout << "Invalid account number!\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    ifstream file(FILE_NAME, ios::binary);
    Account account;

    while (file.read(reinterpret_cast<char*>(&account),
                     sizeof(account))) {

        if (account.getAccountNumber() == number) {
            account.showDetails();
            return;
        }
    }

    cout << "Account not found!\n";
}

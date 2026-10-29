
#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits>
#include <cstring>
#include <cstdio>
#include <string>
#include <cctype>
#include <cmath>

using namespace std;

class Account {
private:
    int accountNumber;
    char name[50];
    char accountType[20];
    double balance;

public:
    Account() {
        accountNumber = 0;
        strcpy(name, "");
        strcpy(accountType, "");
        balance = 0.0;
    }

    void createAccount() {
        cout << "\nEnter Account Number: ";
        cin >> accountNumber;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter Customer Name: ";
        cin.getline(name, 50);

        cout << "Enter Account Type (Savings/Current): ";
        cin.getline(accountType, 20);

        cout << "Enter Initial Deposit: ";
        cin >> balance;

        if (!cin || accountNumber <= 0 ||
            strlen(name) == 0 || balance < 0 ||
            !isfinite(balance)) {
            cout << "Invalid account details!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            accountNumber = 0;
            strcpy(name, "");
            strcpy(accountType, "");
            balance = 0.0;
            return;
        }

        if (strlen(accountType) == 0) {
            cout << "Account type cannot be empty!\n";
            accountNumber = 0;
            strcpy(name, "");
            balance = 0.0;
            return;
        }

        if (cin.peek() != '\n' && cin.peek() != EOF) {
            cout << "Invalid deposit amount!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            accountNumber = 0;
            strcpy(name, "");
            strcpy(accountType, "");
            balance = 0.0;
            return;
        }

        cout << "\nAccount created successfully!\n";
    }

    void displayAccount() const {
        cout << left
             << setw(15) << accountNumber
             << setw(25) << name
             << setw(15) << accountType
             << fixed << setprecision(2)
             << balance << '\n';
    }

    void modifyAccount() {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter New Customer Name: ";
        cin.getline(name, 50);

        cout << "Enter New Account Type (Savings/Current): ";
        cin.getline(accountType, 20);

        if (strlen(name) == 0 || strlen(accountType) == 0) {
            cout << "Name and account type cannot be empty!\n";
        } else {
            cout << "Account details updated successfully!\n";
        }
    }

    void deposit(double amount) {
        balance += amount;
        cout << fixed << setprecision(2)
             << "Deposit successful! New balance: Rs. "
             << balance << '\n';
    }

    bool withdraw(double amount) {
        if (amount <= 0 || !isfinite(amount)) {
            cout << "Invalid withdrawal amount!\n";
            return false;
        }

        if (amount > balance) {
            cout << "Insufficient balance!\n";
            return false;
        }

        balance -= amount;
        cout << fixed << setprecision(2)
             << "Withdrawal successful! New balance: Rs. "
             << balance << '\n';
        return true;
    }

    int getAccountNumber() const {
        return accountNumber;
    }

    void showDetails() const {
        cout << "\nAccount Number : " << accountNumber
             << "\nCustomer Name  : " << name
             << "\nAccount Type   : " << accountType
             << "\nBalance        : Rs. "
             << fixed << setprecision(2) << balance << '\n';
    }

    bool depositMoney(double amount) {
        if (amount <= 0 || !isfinite(amount) ||
            !isfinite(balance + amount)) {
            cout << "Invalid deposit amount!\n";
            return false;
        }

        deposit(amount);
        return true;
    }
};

const char* FILE_NAME = "bank.dat";

// Check whether an account number already exists.
bool accountExists(int number) {
    ifstream file(FILE_NAME, ios::binary);
    Account account;

    while (file.read(reinterpret_cast<char*>(&account),
                     sizeof(account))) {
        if (account.getAccountNumber() == number)
            return true;
    }
    return false;
}

// Create a new account.
void createNewAccount() {
    Account account;
    account.createAccount();

    if (account.getAccountNumber() <= 0)
        return;

    if (accountExists(account.getAccountNumber())) {
        cout << "Account number already exists!\n";
        return;
    }

    ofstream file(FILE_NAME, ios::binary | ios::app);

    if (!file) {
        cout << "Unable to open the data file!\n";
        return;
    }

    file.write(reinterpret_cast<char*>(&account), sizeof(account));

    if (file)
        cout << "Account saved successfully!\n";
    else
        cout << "Error saving account!\n";
}

// Display all accounts.
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

// Search for an account.
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

// Deposit money.
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

// Withdraw money.
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

// Modify an account's customer details.
void modifyAccount() {
    int number;

    cout << "Enter Account Number to Modify: ";
    if (!(cin >> number)) {
        cout << "Invalid account number!\n";
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
            account.showDetails();
            account.modifyAccount();

            file.seekp(-static_cast<streamoff>(sizeof(account)),
                       ios::cur);
            file.write(reinterpret_cast<char*>(&account),
                       sizeof(account));

            cout << (file ? "Changes saved.\n"
                          : "Error updating file!\n");
            return;
        }
    }

    cout << "Account not found!\n";
}

// Delete an account.
void deleteAccount() {
    int number;

    cout << "Enter Account Number to Delete: ";
    if (!(cin >> number)) {
        cout << "Invalid account number!\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    ifstream inFile(FILE_NAME, ios::binary);

    if (!inFile) {
        cout << "No account records found.\n";
        return;
    }

    ofstream outFile("temp.dat", ios::binary);
    Account account;
    bool found = false;

    while (inFile.read(reinterpret_cast<char*>(&account),
                       sizeof(account))) {
        if (account.getAccountNumber() == number) {
            found = true;
        } else {
            outFile.write(reinterpret_cast<char*>(&account),
                          sizeof(account));
        }
    }

    inFile.close();
    outFile.close();

    if (!found) {
        remove("temp.dat");
        cout << "Account not found!\n";
        return;
    }

    if (remove(FILE_NAME) != 0) {
        cout << "Unable to replace the original data file!\n";
        return;
    }

    if (rename("temp.dat", FILE_NAME) != 0) {
        cout << "Account data file could not be restored!\n";
        return;
    }

    cout << "Account deleted successfully!\n";
}

int main() {
    int choice;

    do {
        cout << "\n====================================\n";
        cout << "          BANKING SYSTEM\n";
        cout << "====================================\n";
        cout << "1. Create New Account\n";
        cout << "2. Display All Accounts\n";
        cout << "3. Search Account\n";
        cout << "4. Deposit Amount\n";
        cout << "5. Withdraw Amount\n";
        cout << "6. Modify Account\n";
        cout << "7. Delete Account\n";
        cout << "8. Exit\n";
        cout << "====================================\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cout << "Please enter a valid menu number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1:
                createNewAccount();
                break;
            case 2:
                displayAllAccounts();
                break;
            case 3:
                searchAccount();
                break;
            case 4:
                depositMoney();
                break;
            case 5:
                withdrawMoney();
                break;
            case 6:
                modifyAccount();
                break;
            case 7:
                deleteAccount();
                break;
            case 8:
                cout << "Thank you for using the Banking System!\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }

    } while (choice != 8);

    return 0;
}


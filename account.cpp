
#include "bank.h"

const char FILE_NAME[] = "bank.dat";

Account::Account() {
    accountNumber = 0;
    strcpy(name, "");
    strcpy(accountType, "");
    balance = 0.0;
}

bool Account::createAccount() {
    cout << "\nEnter Account Number: ";
    if (!(cin >> accountNumber)) {
        cout << "Invalid account number!\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter Customer Name: ";
    cin.getline(name, 50);

    cout << "Enter Account Type (Savings/Current): ";
    cin.getline(accountType, 20);

    cout << "Enter Initial Deposit: ";

    if (!(cin >> balance) || accountNumber <= 0 ||
        strlen(name) == 0 || strlen(accountType) == 0 ||
        balance < 0 || !isfinite(balance)) {

        cout << "Invalid account details!\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Account created successfully!\n";
    return true;
}

void Account::displayAccount() const {
    cout << left
         << setw(15) << accountNumber
         << setw(25) << name
         << setw(15) << accountType
         << fixed << setprecision(2)
         << balance << '\n';
}

bool Account::modifyAccount() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter New Customer Name: ";
    cin.getline(name, 50);

    cout << "Enter New Account Type: ";
    cin.getline(accountType, 20);

    if (strlen(name) == 0 || strlen(accountType) == 0) {
        cout << "Invalid details!\n";
        return false;
    }

    cout << "Account details updated successfully!\n";
    return true;
}

void Account::deposit(double amount) {
    balance += amount;

    cout << fixed << setprecision(2)
         << "Deposit successful! New balance: Rs. "
         << balance << '\n';
}

bool Account::withdraw(double amount) {
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

int Account::getAccountNumber() const {
    return accountNumber;
}

void Account::showDetails() const {
    cout << "\nAccount Number : " << accountNumber
         << "\nCustomer Name  : " << name
         << "\nAccount Type   : " << accountType
         << "\nBalance        : Rs. "
         << fixed << setprecision(2) << balance << '\n';
}

bool Account::depositMoney(double amount) {
    if (amount <= 0 || !isfinite(amount) ||
        !isfinite(balance + amount)) {
        cout << "Invalid deposit amount!\n";
        return false;
    }

    deposit(amount);
    return true;
}

// Check existing account
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

// Create new account
void createNewAccount() {
    Account account;

    if (!account.createAccount())
        return;

    if (accountExists(account.getAccountNumber())) {
        cout << "Account number already exists!\n";
        return;
    }

    ofstream file(FILE_NAME, ios::binary | ios::app);

    if (!file) {
        cout << "Unable to open data file!\n";
        return;
    }

    file.write(reinterpret_cast<char*>(&account),
               sizeof(account));

    cout << (file ? "Account saved successfully!\n"
                  : "Error saving account!\n");
}

// Modify account
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

            if (account.modifyAccount()) {
                file.seekp(-static_cast<streamoff>(sizeof(account)),
                           ios::cur);

                file.write(reinterpret_cast<char*>(&account),
                           sizeof(account));

                cout << (file ? "Changes saved!\n"
                              : "Error updating file!\n");
            }

            return;
        }
    }

    cout << "Account not found!\n";
}

// Delete account
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

    if (!outFile) {
        cout << "Unable to create temporary file!\n";
        return;
    }

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
        cout << "Unable to replace original file!\n";
        return;
    }

    if (rename("temp.dat", FILE_NAME) != 0) {
        cout << "Unable to restore account data file!\n";
        return;
    }

    cout << "Account deleted successfully!\n";
}

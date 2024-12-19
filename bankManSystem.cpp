#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
using namespace std;

void saveAccountData(const string &filename, double balance);
double loadAccountBalance(const string &filename);

class Account {
protected:
    double balance;

public:
    Account(double b = 0) : balance(b) {}

    virtual void deposit(double amount) {
        balance += amount;
        cout << "Deposit successful! New balance: Rs" << balance << endl;
    }

    virtual void withdraw(double amount) {
        if (balance >= amount) {
            balance -= amount;
            cout << "Withdraw successful! New balance: Rs" << balance << endl;
        } else {
            cout << "Insufficient balance" << endl;
        }
    }

    double getBalance() const {
        return balance;
    }

    void setBalance(double b) {
        balance = b;
    }

    virtual string getAccountType() const = 0;
};

class SavingAccount : public Account {
private:
    double interestrate;

public:
    SavingAccount(double interest = 0.03, double balance = 0) : Account(balance), interestrate(interest) {}

    void calculateinterest() {
        balance += balance * interestrate;
    }

    double getinterestrate() const {
        return interestrate;
    }
     
    string getAccountType() const override {
        return "Saving";
    }
};

class CurrentAccount : public Account {
private:
    double minimumBalance;
    double penaltyFee;

public:
    CurrentAccount(double minBalance = 1000, double penalty = 50, double balance = 0) : Account(balance), minimumBalance(minBalance), penaltyFee(penalty) {}

    void checkMinimumBalance() {
        if (balance < minimumBalance) {
            balance -= penaltyFee;
            cout << "Penalty fee charged! New balance: Rs" << balance << endl;
        }
    }

    string getAccountType() const override {
        return "Current";
    }
};

class bankmanagementsystem {
protected:
    string accountholder;
    string pincode;
    string password;
    string accountno;
    double balance;
    Account* acc; 

public:
    void createAccount() {
        cout << "Enter account holder name: ";
        cin >> accountholder;
        cout << "Enter account no: ";
        cin >> accountno;
        cout << "Enter balance: ";
        cin >> balance;

        cout << "Enter pincode of five digits: ";
        pincode = "";
        for (int i = 0; i < 5; i++) {
            char c;
            c = getch();
            cout << "*";
            pincode += c;
        }
        cout << endl;

        char choice;
        cout << "Do you want to review your pincode ('y'/'n'): ";
        cin >> choice;
        if (choice == 'Y' || choice == 'y') {
            cout << "\nYour pincode: " << pincode << endl;
        }

        cout << "Enter password (password must be strong, do not exceed  by 8 characters): ";
        password = "";
        for (int i = 0; i < 8; i++) {
            char ch;
            ch = getch();
            cout << "*";
            password += ch;
        }
        cout << endl;

        cout << "Do you want to review your password ('y'/'n'): ";
        cin >> choice;
        if (choice == 'Y' || choice == 'y') {
            cout << "\nYour password: " << password << endl;
        }
        char acctype1;
        cout << "Enter account type 's' for saving and 'c' for current: ";
        cin >> acctype1;
        if (acctype1 == 's') {
            acc = new SavingAccount(0.03, balance);
            saveAccountData("savingAccount1.txt", balance );
        } else {
            acc = new CurrentAccount(1000, 50, balance);  
            saveAccountData("currentAccount1.txt", balance);
        }

        cout << "Account created successfully!\n";
    }

    void showAccount() {
        cout << "Account Holder Name is: " << accountholder << endl;
        cout << "Account number is: " << accountno << endl;
        cout << "Your Balance is: " << balance << endl;
        cout << "Pincode is: " << pincode << endl;
        cout << "Password: " << password << endl;
        cout << "Account Type: " << acc->getAccountType() << endl;
    }
};


class Person {
protected:
    int id;
    string username;
    string email;
    string address;
    string phoneno;

public:
    virtual void displayinfo() = 0;
    virtual void persongetinfo() = 0;
};

class Employee : public Person {
private:
    string designation;
    Account* account;

public:
    void persongetinfo() override {
        cout << "Enter your ID: ";
        cin >> id;
        cout << "Enter your username/name: ";
        cin >> username;
        cout << "Enter your Email: ";
        cin >> email;
        cout << "Enter your Address: ";
        cin >> address;
        cout << "Enter your phone no: ";
        cin >> phoneno;
        cout << "Enter your designation: ";
         cin >> designation;
        double initialBalance;
        cout << "Enter initial balance for your account: ";
        cin >> initialBalance;
        char acctype;
        cout << "Enter account type 's' for saving and 'c' for current: ";
        cin >> acctype;

        if (acctype == 's') {
            account = new SavingAccount(0.03, initialBalance);
            saveAccountData("savingAccount.txt", initialBalance);
        } else {
            account = new CurrentAccount(1000, 50, initialBalance);
            saveAccountData("currentAccount.txt", initialBalance);
        }
    

        ofstream outFile("Employee.txt", ios::app);
        if (outFile.is_open()) {
            outFile << id << " " << username << " " << email << " " << address << " " << phoneno << " " << designation << " " << account->getBalance() << endl;
            outFile.close();
        }
    }

    void displayinfo() override {
        cout << "Id: " << id << endl;
        cout << "Name: " << username << endl;
        cout << "Email: " << email << endl;
        cout << "Address: " << address << endl;
        cout << "Phone no: " << phoneno << endl;
        cout << "Designation: " << designation << endl;
        cout << "Account Balance: Rs" << account->getBalance() << endl;
        cout << "Account Type: " << account->getAccountType() << endl;
    }
};

class Customer : public Person {
private:
    Account* account;

public:
    void persongetinfo() override {
        cout << "Enter your ID: ";
        cin >> id;
        cout << "Enter your username/name: ";
        cin >> username;
        cout << "Enter your Email: ";
        cin >> email;
        cout << "Enter your Address: ";
         cin >> address;
        cout << "Enter your phone no: ";
        cin >> phoneno;

        double initialBalance;
        cout << "Enter initial balance for your account: ";
        cin >> initialBalance;
        char acctype;
        cout << "Enter account type 's' for saving and 'c' for current: ";
        cin >> acctype;

        if (acctype == 's') {
            account = new SavingAccount(0.03, initialBalance);
            saveAccountData("savingAccount.txt", initialBalance);
        } else {

            account = new CurrentAccount(1000, 50, initialBalance);
            saveAccountData("currentAccount.txt", initialBalance);
        }
        

        ofstream outFile("Customer.txt", ios::app);
        if (outFile.is_open()) {
            outFile << id << " " << username << " " << email << " " << address << " " << phoneno << " " << account->getBalance() << endl;
            outFile.close();
        }
    }

    void displayinfo() override {
        cout << "ID: " << id << endl;
        cout << "Name: " << username << endl;
        cout << "Email: " << email << endl;
        cout << "Address: " << address << endl;
        cout << "Phone no: " << phoneno << endl;
        cout << "Account Balance: Rs" << account->getBalance() << endl;
        cout << "Account Type: " << account->getAccountType() << endl;
    }
};

class BankingChannel {
public:
    virtual void performTransaction(Account *account, double amount, const string &type) = 0;
    virtual void displayChannelInfo() const = 0;
};

class ATM : public BankingChannel {
public:
    void performTransaction(Account *account, double amount, const string &type) override {
        if (type == "deposit") {
            account->deposit(amount);
            cout << "Deposited " << amount << " via ATM." << endl;
        } else if (type == "withdraw") {
            account->withdraw(amount);
            cout << "Withdrew " << amount << " via ATM." << endl;
        }
    }

    void displayChannelInfo() const override {
        cout << "Channel: ATM" << endl;
    }
};

class BankCashier : public BankingChannel {
public:
    void performTransaction(Account *account, double amount, const string &type) override {
        if (type == "deposit") {
            account->deposit(amount);
            cout << "Deposited " << amount << " via Bank Cashier." << endl;
        } else if (type == "withdraw") {
            account->withdraw(amount);
            cout << "Withdrew " << amount << " via Bank Cashier." << endl;
        }
    }

    void displayChannelInfo() const override {
        cout << "Channel: Bank Cashier" << endl;
    }
};

class MobileApplication : public BankingChannel {
public:
    void performTransaction(Account *account, double amount, const string &type) override {
        if (type == "deposit") {
            account->deposit(amount);
            cout << "Deposited " << amount << " via Mobile Application." << endl;
        } else if (type == "withdraw") {
            account->withdraw(amount);
            cout << "Withdrew " << amount << " via Mobile Application." << endl;
        }
    }

    void displayChannelInfo() const override {
        cout << "Channel: Mobile Application" << endl;
    }
};

class InternetBanking : public BankingChannel {
public:
    void performTransaction(Account *account, double amount, const string &type) override {
        if (type == "deposit") {
            account->deposit(amount);
            cout << "Deposited " << amount << " via Internet Banking." << endl;
        } else if (type == "withdraw") {
            account->withdraw(amount);
            cout << "Withdrew " << amount << " via Internet Banking." << endl;
        }
    }

    void displayChannelInfo() const override {
        cout << "Channel: Internet Banking" << endl;
    }
};

double loadAccountBalance(const string &filename) {
    ifstream inFile(filename);
    double balance = 0;
    if (inFile.is_open()) {
        inFile >> balance;
        inFile.close();
    }
    return balance;
}

void saveAccountData(const string &filename, double balance) {
    ofstream outFile(filename);
    if (outFile.is_open()) {
        outFile << balance;
        outFile.close();
    }
}

void addTransactionAmount(const string &filename, double amount, const string &type) {
    double currentBalance = loadAccountBalance(filename);
    if (type == "deposit") {
        currentBalance += amount;
    } else if (type == "withdraw" && currentBalance >= amount) {
        currentBalance -= amount;
    } else {
        cout << "Insufficient balance for withdrawal." << endl;
        return;
    }
    saveAccountData(filename, currentBalance);
    cout << "Transaction successful! Updated balance: Rs" << currentBalance << endl;
}

int main() {
    bankmanagementsystem bms;
    Employee e;
    Customer c;

    char ch;
    cout << "** Welcome to our Bank Management System ***" << endl;
    while (true) {
        cout << "\n1. Create Account\n";
        cout << "2. Employee Info\n";
        cout << "3. Customer Info\n";
        cout << "4. Perform Transaction\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> ch;
        switch (ch) {
            case '1': {
                bms.createAccount();
                bms.showAccount();
                break;
            }
            case '2': {
                e.persongetinfo();
                cout << "Employee Information" << endl;
                e.displayinfo();
                break;
            }
            case '3': {
                c.persongetinfo();
                cout << "Customer Information" << endl;
                c.displayinfo();

                break;
            }

            case '4': {
                string accountType;
                cout << "Choose account type (Saving/Current): ";
                cin >> accountType;

                char userType;
                cout << "Enter user type (c for Customer, e for Employee): ";
                cin >> userType;

                BankingChannel *channel = nullptr;
                char channelChoice;
                cout << "Choose transaction channel:\n";
                cout << "1. ATM\n";
                cout << "2. Bank Cashier\n";
                cout << "3. Mobile Application\n";
                cout << "4. Internet Banking\n";
                cout << "Enter choice: ";
                cin >> channelChoice;

                switch (channelChoice) {
                    case '1': channel = new ATM(); break;
                    case '2': channel = new BankCashier(); break;
                    case '3': channel = new MobileApplication(); break;
                    case '4': channel = new InternetBanking(); break;
                    default: cout << "Invalid choice.\n"; break;
                }

                if (channel) {
                    char transactionType;
                    double amount;
                    cout << "Enter transaction type (d for deposit, w for withdraw): ";
                    cin >> transactionType;
                    cout << "Enter amount: ";
                    cin >> amount;

                    if (transactionType == 'd') {
                        addTransactionAmount(accountType == "Saving" ? "savingAccount.txt" : "currentAccount.txt", amount, "deposit");
                    } else if (transactionType == 'w') {
                        addTransactionAmount(accountType == "Saving" ? "savingAccount.txt" : "currentAccount.txt", amount, "withdraw");
                    } else {
                        cout << "Invalid transaction type.\n";
                    }
                    delete channel;
                }
                break;
            }
            case '5': {
                cout << "Thank you for using our service!" << endl;
                exit(0);
            }
            default: {
                cout << "Invalid choice. Try again." << endl;
                break;
            }
        }
    }
    return 0;
}

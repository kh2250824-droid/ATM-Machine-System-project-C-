#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

class Account {
protected:
    int accountNumber;
    string holderName;
    double balance;
    string pin;

public:
    Account() {
        accountNumber = 0;
        holderName = "";
        balance = 0.0;
        pin = "0000";
    }

    Account(int accNo, string name, double bal, string p) {
        accountNumber = accNo;
        holderName = name;
        balance = bal;
        pin = p;
    }

    virtual void displayAccount() = 0; 

    bool verifyPIN(string enteredPin) {
        return pin == enteredPin;
    }

    int getAccountNumber() {
        return accountNumber;
    }

    double getBalance() {
        return balance;
    }

    virtual void deposit(double amount) {
        balance += amount;
    }

    virtual bool withdraw(double amount) {
        if (amount <= balance) {
            balance -= amount;
            return true;
        }
        return false;
    }

    virtual ~Account() {
            }
};

class SavingsAccount : public Account {
private:
    double interestRate;

public:
    SavingsAccount() : Account() {
        interestRate = 0.02;
    }

    SavingsAccount(int accNo, string name, double bal, string p, double rate)
        : Account(accNo, name, bal, p) {
        interestRate = rate;
    }

    void displayAccount() override {
        cout << "\n----- Account Details -----\n";
        cout << "Account No   : " << accountNumber << endl;
        cout << "Holder Name  : " << holderName << endl;
        cout << "Balance      : " << fixed << setprecision(2) << balance << endl;
        cout << "Interest Rate: " << interestRate * 100 << "%\n";
    }

    void addInterest() {
        balance += balance * interestRate;
    }
};
class ATM {
private:
    SavingsAccount account;

public:
    ATM() {}

    ATM(SavingsAccount acc) {
        account = acc;
    }

    void showMenu() {
        cout << "\n========= ATM MENU =========\n";
        cout << "1. Check Balance\n";
        cout << "2. Deposit Money\n";
        cout << "3. Withdraw Money\n";
        cout << "4. Account Details\n";
        cout << "5. Add Interest\n";
        cout << "6. Exit\n";
        cout << "============================\n";
    }

    void start() {
        string enteredPin;
        cout << "Enter PIN: ";
        cin >> enteredPin;

        if (!account.verifyPIN(enteredPin)) {
            cout << "Invalid PIN! Access Denied.\n";
            return;
        }

        int choice;
        double amount;

        do {
            showMenu();
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    cout << "Current Balance: " << account.getBalance() << endl;
                    break;

                case 2:
                    cout << "Enter deposit amount: ";
                    cin >> amount;
                    account.deposit(amount);
                    cout << "Deposit Successful.\n";
                    break;

                case 3:
                    cout << "Enter withdraw amount: ";
                    cin >> amount;
                    if (account.withdraw(amount)) {
                        cout << "Withdrawal Successful.\n";
                    } else {
                        cout << "Insufficient Balance.\n";
                    }
                    break;

                case 4:
                    account.displayAccount();
                    break;

                case 5:
                    account.addInterest();
                    cout << "Interest Added Successfully.\n";
                    break;

                case 6:
                    cout << "Thank you for using ATM.\n";
                    saveToFile();
                    break;

                default:
                    cout << "Invalid Choice.\n";
            }
        } while (choice != 6);
    }
    void saveToFile() {
        ofstream file("account_data.txt");
        if (file.is_open()) {
            file << account.getAccountNumber() << endl;
            file << account.getBalance() << endl;
            file.close();
        }
    }
};
class BankUtility {
public:
    static SavingsAccount createAccount() {
        int accNo;
        string name, pin;
        double balance;

        cout << "Enter Account Number: ";
        cin >> accNo;
        cin.ignore();

        cout << "Enter Account Holder Name: ";
        getline(cin, name);

        cout << "Set 4-digit PIN: ";
        cin >> pin;

        cout << "Enter Initial Balance: ";
        cin >> balance;

        return SavingsAccount(accNo, name, balance, pin, 0.03);
    }
};

int main() {
    cout << "===== Welcome to ATM System =====\n";

    SavingsAccount userAccount = BankUtility::createAccount();
    ATM atm(userAccount);
    atm.start();

    return 0;
}

OUTPUT:


===== Welcome to ATM System =====
Enter Account Number: 76890123412345
Enter Account Holder Name: Set 4-digit PIN: Enter Initial Balance: Enter PIN: 
========= ATM MENU =========
1. Check Balance
2. Deposit Money
3. Withdraw Money
4. Account Details
5. Add Interest
6. Exit
============================
Enter your choice: Invalid Choice.

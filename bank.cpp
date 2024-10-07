#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <ctime>
#include <cstdlib>

using namespace std;

class Admin {
private:
    string username;
    string email;
    string password;
    string phoneNumber;
    string nationalCode;

public:
    Admin(string user, string mail, string pass, string phone, string national)
        : username(user), email(mail), password(pass), phoneNumber(phone), nationalCode(national) {}

    bool login(const string& user, const string& pass) {
        return (username == user && password == pass);
    }
};

class Employee : public Admin {
private:
    double salary;

public:
    Employee(string user, string mail, string pass, string phone, string national, double sal)
        : Admin(user, mail, pass, phone, national), salary(sal) {}
};

class Account;

class Customer {
private:
    string username;
    string password;
    string email;
    string phoneNumber;
    vector<Account*> accounts;
    bool isApproved;

public:
    static vector<Customer*> pendingRegistrations;

    Customer(string user, string pass, string mail, string phone)
        : username(user), password(pass), email(mail), phoneNumber(phone), isApproved(false) {
        pendingRegistrations.push_back(this);
    }

    bool login(const string& user, const string& pass) {
        return (username == user && password == pass);
    }

    void registerCustomer(Employee& employee) {
        isApproved = true;
        auto it = find(pendingRegistrations.begin(), pendingRegistrations.end(), this);
        if (it != pendingRegistrations.end()) {
            pendingRegistrations.erase(it);
        }
    }

    void createAccount(Account* account) {
        if (isApproved) {
            accounts.push_back(account);
        } else {
            cout << "Customer is not approved." << endl;
        }
    }

    vector<Account*> getAccounts() const {
        return accounts;
    }
};

vector<Customer*> Customer::pendingRegistrations;

class Account {
private:
    static int nextAccountNumber;
    int accountNumber;
    double balance;
    time_t creationDate;
    Customer* owner;

public:
    Account(Customer* cust) : owner(cust), balance(0.0) {
        accountNumber = ++nextAccountNumber;
        creationDate = time(nullptr);
    }

    void deposit(double amount) {
        balance += amount;
    }

    void withdraw(double amount) {
        if (amount <= balance) {
            balance -= amount;
        } else {
            cout << "Insufficient funds!" << endl;
        }
    }

    double getBalance() const {
        return balance;
    }

    int getAccountNumber() const {
        return accountNumber;
    }
};

int Account::nextAccountNumber = 0;

class Card {
private:
    string cardNumber;
    string expirationDate;
    string cvv2;
    string pin;
    bool isActive;

public:
    Card(string number, string expiry, string cvv)
        : cardNumber(number), expirationDate(expiry), cvv2(cvv), isActive(true) {
        pin = to_string(rand() % 10000);
    }

    void deactivate() {
        isActive = false;
    }

    void changePin(const string& newPin) {
        pin = newPin;
    }

    bool isCardActive() const {
        return isActive;
    }

    string getCardNumber() const {
        return cardNumber;
    }
};

class Transaction {
private:
    double amount;
    time_t date;
    string sender;
    string receiver;

public:
    Transaction(double amt, const string& sndr, const string& rcvr)
        : amount(amt), sender(sndr), receiver(rcvr) {
        date = time(nullptr);
    }
};

class Loan {
private:
    double amount;
    string status;
    time_t loanDate;
    Customer* borrower;

public:
    Loan(double amt, Customer* cust) : amount(amt), borrower(cust), status("Active") {
        loanDate = time(nullptr);
    }

    void closeLoan() {
        status = "Closed";
    }

    double getLoanAmount() const {
        return amount;
    }
};

int main() {
    
    Employee emp("admin", "admin@bank.com", "password", "123456789", "987654321", 5000);
    Customer cust("user1", "pass1", "user1@mail.com", "123456789");
    
    cust.registerCustomer(emp); 
    Account* acc1 = new Account(&cust);
    cust.createAccount(acc1);
    
    acc1->deposit(1000);
    cout << "Account Balance: " << acc1->getBalance() << endl;

    return 0;
}

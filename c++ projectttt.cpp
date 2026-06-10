#include <iostream>
#include <string>
#include <cstdlib>
#include <limits>
#include <iomanip>
using namespace std;

// ---------------------------------------------
//  VALIDATION FUNCTIONS
// ---------------------------------------------
bool isValidPhone(string phone) {
    if (phone.length() != 11) return false;
    for (int i = 0; i < (int)phone.length(); i++) {
        if (phone[i] < '0' || phone[i] > '9') return false;
    }
    return true;
}

bool isValidCNIC(string cnic) {
    if (cnic.length() != 15) return false;
    for (int i = 0; i < 15; i++) {
        if (i == 5 || i == 13) {
            if (cnic[i] != '-') return false;
        } else {
            if (cnic[i] < '0' || cnic[i] > '9') return false;
        }
    }
    return true;
}

// Safe integer input — clears buffer on bad input
int getChoice() {
    int val;
    while (true) {
        cin >> val;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "  [!] Invalid input. Please enter a number: ";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return val;
        }
    }
}

// ---------------------------------------------
//  BANK ACCOUNT CLASS
// ---------------------------------------------
class BankAccount {
private:
    string ownerName, username, password, city, cnic, phone;
    double balance;
    int    accountNumber;
    bool   active;

public:
    BankAccount() {
        accountNumber = 0;
        balance       = 0.0;
        active        = false;
    }

    void createAccount(int accNo, string name, string user, string pass,
                       string c, string cn, string ph) {
        accountNumber = accNo;
        ownerName     = name;
        username      = user;
        password      = pass;
        city          = c;
        cnic          = cn;
        phone         = ph;
        balance       = 0.0;
        active        = true;
    }

    string getUsername()  { return username; }
    string getPassword()  { return password; }
    string getOwnerName() { return ownerName; }
    int    getAccNo()     { return accountNumber; }
    double getBalance()   { return balance; }
    bool   isActive()     { return active; }

    void deposit(double amount) {
        if (amount <= 0) {
            cout << "\n  [!] Invalid amount. Please enter a positive value." << endl;
        } else {
            balance += amount;
            cout << "\n  [+] Rs. " << fixed << setprecision(2) << amount << " deposited successfully!" << endl;
            cout << "  New Balance: Rs. " << fixed << setprecision(2) << balance << endl;
        }
    }

    void withdraw(double amount) {
        if (amount <= 0) {
            cout << "\n  [!] Invalid amount." << endl;
        } else if (amount > balance) {
            cout << "\n  [!] Insufficient balance!" << endl;
            cout << "  Available Balance: Rs. " << fixed << setprecision(2) << balance << endl;
        } else {
            balance -= amount;
            cout << "\n  [-] Rs. " << fixed << setprecision(2) << amount << " withdrawn successfully!" << endl;
            cout << "  Remaining Balance: Rs. " << fixed << setprecision(2) << balance << endl;
        }
    }

    void showDetails() {
        cout << "\n  ================================" << endl;
        cout << "  Full Name      : " << ownerName     << endl;
        cout << "  Account Number : " << accountNumber << endl;
        cout << "  CNIC           : " << cnic          << endl;
        cout << "  Phone          : " << phone         << endl;
        cout << "  City           : " << city          << endl;
        cout << "  Username       : " << username      << endl;
        cout << "  Balance        : Rs. " << fixed << setprecision(2) << balance   << endl;
        cout << "  ================================" << endl;
    }
};

// ---------------------------------------------
//  HELPER FUNCTIONS
// ---------------------------------------------
void printLine() {
    cout << "  ------------------------------------------" << endl;
}

void printHeader(string title) {
    cout << "\n  ==========================================" << endl;
    cout << "      NATIONAL BANK  |  " << title            << endl;
    cout << "  ==========================================" << endl;
}

void pressEnter() {
    system("pause");
}

// ---------------------------------------------
//  ACCOUNT MENU
// ---------------------------------------------
void accountMenu(BankAccount &acc) {
    int  choice;
    bool loggedIn = true;

    while (loggedIn) {
        printHeader("ACCOUNT MENU");
        cout << "  Welcome, " << acc.getOwnerName() << "!" << endl;
        cout << "  Account No: " << acc.getAccNo()  << endl;
        printLine();
        cout << "  [1] Check Balance"   << endl;
        cout << "  [2] Deposit Money"   << endl;
        cout << "  [3] Withdraw Money"  << endl;
        cout << "  [4] Account Details" << endl;
        cout << "  [5] Logout"          << endl;
        printLine();
        cout << "  Enter Choice: ";
        choice = getChoice();

        switch (choice) {

            case 1:
                printHeader("CHECK BALANCE");
                cout << "  Your Balance: Rs. " << fixed << setprecision(2) << acc.getBalance() << endl;
                pressEnter();
                break;

            case 2: {
                double amt;
                printHeader("DEPOSIT MONEY");
                cout << "  Enter amount to deposit: Rs. ";
                cin >> amt;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                acc.deposit(amt);
                pressEnter();
                break;
            }

            case 3: {
                double amt;
                printHeader("WITHDRAW MONEY");
                cout << "  Enter amount to withdraw: Rs. ";
                cin >> amt;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                acc.withdraw(amt);
                pressEnter();
                break;
            }

            case 4:
                printHeader("ACCOUNT DETAILS");
                acc.showDetails();
                pressEnter();
                break;

            case 5:
                cout << "\n  Logged out successfully. Goodbye, "
                     << acc.getOwnerName() << "!" << endl;
                loggedIn = false;
                pressEnter();
                break;

            default:
                cout << "\n  [!] Invalid choice. Please enter 1-5." << endl;
                pressEnter();
                break;
        }
    }
}

// ---------------------------------------------
//  MAIN
// ---------------------------------------------
int main() {

    const int MAX = 20;
    BankAccount accounts[MAX];
    int  total   = 0;
    int  nextAcc = 1001;
    int  choice;
    bool running = true;

    while (running) {
        printHeader("MAIN MENU");
        cout << "  [1] Sign Up  - Create New Account" << endl;
        cout << "  [2] Login    - Access Your Account" << endl;
        cout << "  [3] View All Accounts"              << endl;
        cout << "  [4] Exit"                           << endl;
        printLine();
        cout << "  Enter Choice: ";
        choice = getChoice();

        switch (choice) {

            // -------------------------------------
            //  SIGN UP
            // -------------------------------------
            case 1: {
                printHeader("SIGN UP - CREATE NEW ACCOUNT");

                if (total >= MAX) {
                    cout << "\n  [!] Bank is full. Cannot create more accounts." << endl;
                    pressEnter();
                    break;
                }

                string name, user, pass, pass2, cnic, phone, city;

                // STEP 1
                cout << "\n  ===== STEP 1: Personal Details =====\n" << endl;

                cout << "  Full Name    : ";
                getline(cin, name);

                // CNIC validation loop
                while (true) {
                    cout << "  CNIC         : ";
                    getline(cin, cnic);
                    if (isValidCNIC(cnic)) {
                        break;
                    } else {
                        cout << "\n  [!] Invalid CNIC!" << endl;
                        cout << "      Correct Format : 12345-6789012-3" << endl;
                        cout << "      (5 digits - 7 digits - 1 digit)" << endl;
                        cout << "      Please try again.\n" << endl;
                    }
                }

                // Phone validation loop
                while (true) {
                    cout << "  Phone Number : ";
                    getline(cin, phone);
                    if (isValidPhone(phone)) {
                        break;
                    } else {
                        cout << "\n  [!] Invalid Phone Number!" << endl;
                        cout << "      Correct Format : 03001234567" << endl;
                        cout << "      (Exactly 11 digits, numbers only)" << endl;
                        cout << "      Please try again.\n" << endl;
                    }
                }

                cout << "  City         : ";
                getline(cin, city);

                // STEP 2
                cout << "\n  ===== STEP 2: Create Login Credentials =====\n" << endl;

                // Username — check if already taken
                while (true) {
                    cout << "  Choose Username  : ";
                    getline(cin, user);

                    bool taken = false;
                    for (int k = 0; k < total; k++) {
                        if (accounts[k].getUsername() == user) {
                            taken = true;
                            break;
                        }
                    }
                    if (taken) {
                        cout << "\n  [!] Username already taken! Please choose a different one.\n" << endl;
                    } else {
                        break;
                    }
                }

                // Password
                cout << "  Choose Password  : ";
                getline(cin, pass);

                // Confirm password
                while (true) {
                    cout << "  Confirm Password : ";
                    getline(cin, pass2);
                    if (pass == pass2) {
                        break;
                    } else {
                        cout << "\n  [!] Passwords do not match! Please try again.\n" << endl;
                    }
                }

                // Save
                accounts[total].createAccount(nextAcc, name, user, pass,
                                              city, cnic, phone);
                total++;

                // Activation screen
                cout << "\n  ==========================================" << endl;
                cout << "   [?]  ACCOUNT CREATED AND ACTIVATED!       " << endl;
                cout << "  ==========================================" << endl;
                cout << "  Full Name      : " << name    << endl;
                cout << "  CNIC           : " << cnic    << endl;
                cout << "  Phone          : " << phone   << endl;
                cout << "  City           : " << city    << endl;
                cout << "  Account Number : " << nextAcc << endl;
                cout << "  Username       : " << user    << endl;
                cout << "  ==========================================" << endl;
                cout << "  Your account is now ACTIVE at National Bank." << endl;
                cout << "  Go to Main Menu and select LOGIN to access"   << endl;
                cout << "  your account using your username & password." << endl;
                cout << "  ==========================================" << endl;

                nextAcc++;
                pressEnter();
                break;
            }

            // -------------------------------------
            //  LOGIN
            // -------------------------------------
            case 2: {
                printHeader("LOGIN");

                if (total == 0) {
                    cout << "\n  [!] No accounts found." << endl;
                    cout << "  Please Sign Up first!" << endl;
                    pressEnter();
                    break;
                }

                string user, pass;
                cout << "  Username : ";
                getline(cin, user);
                cout << "  Password : ";
                getline(cin, pass);

                bool found = false;
                for (int i = 0; i < total; i++) {
                    if (accounts[i].getUsername() == user &&
                        accounts[i].getPassword() == pass) {
                        cout << "\n  [?] Login Successful! Welcome, "
                             << accounts[i].getOwnerName() << "!" << endl;
                        pressEnter();
                        accountMenu(accounts[i]);
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    cout << "\n  [!] Incorrect username or password!" << endl;
                    cout << "  If you don't have an account, please Sign Up first." << endl;
                    pressEnter();
                }
                break;
            }

            // -- VIEW ALL -------------------------
            case 3: {
                printHeader("ALL ACCOUNTS");
                if (total == 0) {
                    cout << "\n  No accounts registered yet." << endl;
                } else {
                    for (int i = 0; i < total; i++) {
                        cout << "  [" << i + 1 << "] "
                             << accounts[i].getOwnerName()
                             << "  |  Acc No: "   << accounts[i].getAccNo()
                             << "  |  Username: " << accounts[i].getUsername()
                             << endl;
                    }
                }
                pressEnter();
                break;
            }

            // -- EXIT -----------------------------
            case 4:
                cout << "\n  Thank you for banking with National Bank. Goodbye!" << endl;
                running = false;
                break;

            default:
                cout << "\n  [!] Invalid option. Please enter 1, 2, 3 or 4." << endl;
                pressEnter();
                break;
        }
    }

    return 0;
}

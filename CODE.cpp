#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Blueprint for holding multiple accounts in an array
struct Account
{
    string id;
    string name;
    double balance;
};

// Function Declarations
void add();
void addm();
void dep();
void wth();
void trans();
void showone();
void showall();
void findname();
void findbal();
void del();
bool chk(string id2);
string cleanStr(string str); // Simple utility to clean hidden text symbols

int main()
{
    int op = 0;

    // The menu loop runs until option 11 is selected
    while (op != 11)
    {
        cout << "\nWelcome to the Bank Management System!" << endl;
        cout << "1. Create New Account" << endl;
        cout << "2. Create Multiple New Accounts" << endl;
        cout << "3. Deposit Money" << endl;
        cout << "4. Withdraw Money" << endl;
        cout << "5. Transfer Money" << endl;
        cout << "6. View Account Details" << endl;
        cout << "7. View All Accounts" << endl;
        cout << "8. Search Account by Name" << endl;
        cout << "9. Search Accounts by Balance Greater Than" << endl;
        cout << "10. Delete Account" << endl;
        cout << "11. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> op;

        // Catching input errors (e.g., typing letters instead of numbers)
        if (cin.fail())
        {
            cin.clear();
            string dummy;
            cin >> dummy;
            cout << "Invalid input! Please enter a number." << endl;
            continue;
        }

        switch (op)
        {
        case 1:
            add();
            break;
        case 2:
            addm();
            break;
        case 3:
            dep();
            break;
        case 4:
            wth();
            break;
        case 5:
            trans();
            break;
        case 6:
            showone();
            break;
        case 7:
            showall();
            break;
        case 8:
            findname();
            break;
        case 9:
            findbal();
            break;
        case 10:
            del();
            break;
        case 11:
            cout << "Thank you for using our system. Goodbye!" << endl;
            break;
        default:
            cout << "Invalid choice! Please select between 1 and 11." << endl;
            break;
        }
    }

    return 0;
}

// Beginner-friendly text cleaner: strips out hidden Windows carriage returns ('\r')
string cleanStr(string str)
{
    string res = "";
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] != '\r' && str[i] != '\n')
        {
            res += str[i];
        }
    }
    return res;
}

void add()
{
    string id, n;
    double b;

    cout << "\nCreate New Account" << endl;
    cout << "Enter Account ID: ";
    cin >> id;

    if (chk(id))
    {
        cout << "Account ID already exists!" << endl;
        return;
    }

    cout << "Enter Account Holder's Name: ";
    cin.ignore();
    getline(cin, n);

    cout << "Enter Initial Deposit: ";
    cin >> b;

    if (b < 0)
    {
        cout << "Initial deposit cannot be negative!" << endl;
        return;
    }

    ofstream f1("accounts.txt", ios::app);
    if (!f1)
    {
        cout << "Warning: Could not open file to save data!" << endl;
        return;
    }

    f1 << id << "," << n << "," << b << endl;
    f1.close();

    cout << "Account created successfully!" << endl;
}

void addm()
{
    int count;
    cout << "\n Bulk Account Creation " << endl;
    cout << "How many accounts do you want to add? ";
    cin >> count;

    if (cin.fail() || count <= 0)
    {
        cin.clear();
        string dummy;
        cin >> dummy;
        cout << "Please add a valid number!" << endl;
        return;
    }

    // Creating a dynamic array on the HEAP memory based on the manager's input size
    Account *accountArray = new Account[count];

    for (int i = 0; i < count; i++)
    {
        cout << "\n Entering Details for Account #" << (i + 1) << endl;

        while (true)
        {
            cout << "Enter unique Account ID: ";
            cin >> accountArray[i].id;

            bool existsInFile = chk(accountArray[i].id);
            bool duplicateInBatch = false;

            // Checking the array elements gathered so far to prevent local duplicates
            for (int j = 0; j < i; j++)
            {
                if (accountArray[i].id == accountArray[j].id)
                {
                    duplicateInBatch = true;
                    break;
                }
            }

            if (existsInFile || duplicateInBatch)
            {
                cout << "An account with this ID already exists! Please enter a unique ID." << endl;
            }
            else
            {
                break;
            }
        }

        cout << "Enter Account Holder's Name: ";
        cin.ignore();
        getline(cin, accountArray[i].name);

        cout << "Enter Initial Deposit: ";
        cin >> accountArray[i].balance;

        if (cin.fail() || accountArray[i].balance < 0)
        {
            cin.clear();
            string dummy;
            cin >> dummy;
            cout << "Error: Initial deposit cannot be negative! Setting to 0." << endl;
            accountArray[i].balance = 0;
        }
    }

    ofstream f15("accounts.txt", ios::app);
    if (!f15)
    {
        cout << "Error: Could not open file to save data!" << endl;
        delete[] accountArray; // Free memory safely before leaving if file fails
        return;
    }

    for (int i = 0; i < count; i++)
    {
        f15 << cleanStr(accountArray[i].id) << ","
            << cleanStr(accountArray[i].name) << ","
            << accountArray[i].balance << endl;
    }
    f15.close();

    // Deleting the pointer array to free up the RAM (preventing memory leaks)
    delete[] accountArray;

    cout << "\nAll " << count << " accounts processed and saved successfully!" << endl;
}

bool chk(string id2)
{
    ifstream f2("accounts.txt");
    if (!f2)
        return false;

    string fid, fn, fb;
    while (getline(f2, fid, ',') && getline(f2, fn, ',') && getline(f2, fb))
    {
        if (cleanStr(fid) == id2)
        {
            f2.close();
            return true;
        }
    }
    f2.close();
    return false;
}

void dep()
{
    string id;
    double amt;
    bool f = false;

    cout << "\n--- Deposit Money ---" << endl;
    cout << "Enter Account ID: ";
    cin >> id;

    cout << "Enter Amount to Deposit: ";
    cin >> amt;

    if (amt <= 0)
    {
        cout << "Error: Deposit amount must be greater than zero!" << endl;
        return;
    }

    ifstream f3("accounts.txt");
    ofstream f4("temp.txt");

    if (!f3 || !f4)
    {
        cout << "Error opening file!" << endl;
        return;
    }

    string fid, fn, fb;
    while (getline(f3, fid, ',') && getline(f3, fn, ',') && getline(f3, fb))
    {
        string cid = cleanStr(fid);
        if (cid == id)
        {
            f = true;
            double cur = stod(cleanStr(fb));
            cur += amt;
            f4 << cid << "," << cleanStr(fn) << "," << cur << endl;
        }
        else
        {
            f4 << cid << "," << cleanStr(fn) << "," << cleanStr(fb) << endl;
        }
    }

    f3.close();
    f4.close();

    remove("accounts.txt");
    rename("temp.txt", "accounts.txt");

    if (f)
        cout << "Amount deposited successfully!" << endl;
    else
        cout << "Error: Account ID not found!" << endl;
}

void wth()
{
    string id;
    double amt;
    bool f = false;

    cout << "\n--- Withdraw Money ---" << endl;
    cout << "Enter Account ID: ";
    cin >> id;

    cout << "Enter Amount to Withdraw: ";
    cin >> amt;

    if (amt <= 0)
    {
        cout << "Error: Withdrawal amount must be greater than zero!" << endl;
        return;
    }

    ifstream f5("accounts.txt");
    ofstream f6("temp.txt");

    if (!f5 || !f6)
    {
        cout << "Error opening file!" << endl;
        return;
    }

    string fid, fn, fb;
    while (getline(f5, fid, ',') && getline(f5, fn, ',') && getline(f5, fb))
    {
        string cid = cleanStr(fid);
        if (cid == id)
        {
            f = true;
            double cur = stod(cleanStr(fb));

            if (cur < amt)
            {
                cout << "Error: Insufficient balance! Transaction canceled." << endl;
                f6 << cid << "," << cleanStr(fn) << "," << cleanStr(fb) << endl;
            }
            else
            {
                cur -= amt;
                f6 << cid << "," << cleanStr(fn) << "," << cur << endl;
                cout << "Amount withdrawn successfully!" << endl;
            }
        }
        else
        {
            f6 << cid << "," << cleanStr(fn) << "," << cleanStr(fb) << endl;
        }
    }

    f5.close();
    f6.close();

    remove("accounts.txt");
    rename("temp.txt", "accounts.txt");

    if (!f)
        cout << "Error: Account ID not found!" << endl;
}

void trans()
{
    string id1, id2;
    double amt;

    cout << "\n--- Transfer Money ---" << endl;
    cout << "Enter Source Account ID (From): ";
    cin >> id1;
    cout << "Enter Target Account ID (To): ";
    cin >> id2;

    if (id1 == id2)
    {
        cout << "Error: Source and target accounts cannot be the same!" << endl;
        return;
    }

    cout << "Enter Amount to Transfer: ";
    cin >> amt;

    if (amt <= 0)
    {
        cout << "Error: Transfer amount must be greater than zero!" << endl;
        return;
    }

    if (!chk(id1))
    {
        cout << "Error: Source account ID not found!" << endl;
        return;
    }
    if (!chk(id2))
    {
        cout << "Error: Target account ID not found!" << endl;
        return;
    }

    // Step 1: Pre-verify balance check without writing anything to avoid file corruption
    ifstream f_check("accounts.txt");
    string fid, fn, fb;
    bool has_enough_money = false;

    while (getline(f_check, fid, ',') && getline(f_check, fn, ',') && getline(f_check, fb))
    {
        if (cleanStr(fid) == id1)
        {
            if (stod(cleanStr(fb)) >= amt)
            {
                has_enough_money = true;
            }
            break;
        }
    }
    f_check.close();

    if (!has_enough_money)
    {
        cout << "Error: Source account has insufficient balance!" << endl;
        return;
    }

    // Step 2: Safe Execution
    ifstream f7("accounts.txt");
    ofstream f8("temp.txt");

    while (getline(f7, fid, ',') && getline(f7, fn, ',') && getline(f7, fb))
    {
        string cid = cleanStr(fid);
        double cur = stod(cleanStr(fb));

        if (cid == id1)
        {
            f8 << cid << "," << cleanStr(fn) << "," << (cur - amt) << endl;
        }
        else if (cid == id2)
        {
            f8 << cid << "," << cleanStr(fn) << "," << (cur + amt) << endl;
        }
        else
        {
            f8 << cid << "," << cleanStr(fn) << "," << cleanStr(fb) << endl;
        }
    }

    f7.close();
    f8.close();

    remove("accounts.txt");
    rename("temp.txt", "accounts.txt");
    cout << "Transfer successful!" << endl;
}

void showone()
{
    string id;
    bool f = false;

    cout << "\n--- View Account Details ---" << endl;
    cout << "Enter Account ID: ";
    cin >> id;

    ifstream f9("accounts.txt");
    if (!f9)
    {
        cout << "Error: No account data found!" << endl;
        return;
    }

    string fid, fn, fb;
    while (getline(f9, fid, ',') && getline(f9, fn, ',') && getline(f9, fb))
    {
        string cid = cleanStr(fid);
        if (cid == id)
        {
            f = true;
            cout << "\nAccount Details Found:" << endl;
            cout << "ID: " << cid << endl;
            cout << "Account Holder's Name: " << cleanStr(fn) << endl;
            cout << "Account Balance: $" << cleanStr(fb) << endl;
            break;
        }
    }
    f9.close();

    if (!f)
        cout << "Account ID not found!" << endl;
}

void showall()
{
    ifstream f10("accounts.txt");
    if (!f10)
    {
        cout << "Error: No account data found!" << endl;
        return;
    }

    cout << "\n--- All Registered Accounts ---" << endl;
    cout << "ID\t|\tName\t\t|\tBalance" << endl;
    cout << "----------------------------------------------------" << endl;

    string fid, fn, fb;
    int tot = 0;

    while (getline(f10, fid, ',') && getline(f10, fn, ',') && getline(f10, fb))
    {
        cout << cleanStr(fid) << "\t|" << cleanStr(fn) << "\t\t|$" << cleanStr(fb) << endl;
        tot++;
    }
    f10.close();

    if (tot == 0)
        cout << "The database is currently empty." << endl;
}

void findname()
{
    string sname;
    bool f = false;

    cout << "\n--- Search Account by Name ---" << endl;
    cout << "Enter full or partial name: ";
    cin.ignore();
    getline(cin, sname);

    ifstream f11("accounts.txt");
    if (!f11)
    {
        cout << "Error opening database file!" << endl;
        return;
    }

    string fid, fn, fb;
    cout << "\nMatching Accounts:" << endl;

    while (getline(f11, fid, ',') && getline(f11, fn, ',') && getline(f11, fb))
    {
        string currentName = cleanStr(fn);
        if (currentName.find(sname) != string::npos)
        {
            f = true;
            cout << "ID: " << cleanStr(fid) << " | Name: " << currentName << " | Balance: $" << cleanStr(fb) << endl;
        }
    }
    f11.close();

    if (!f)
        cout << "No accounts match the name search criteria." << endl;
}

void findbal()
{
    double th;
    bool f = false;

    cout << "\n--- Search Accounts by Balance Threshold ---" << endl;
    cout << "Enter minimum balance threshold: ";
    cin >> th;

    ifstream f12("accounts.txt");
    if (!f12)
    {
        cout << "Error opening database file!" << endl;
        return;
    }

    string fid, fn, fb;
    cout << "\nAccounts with balance >= " << th << ":" << endl;

    while (getline(f12, fid, ',') && getline(f12, fn, ',') && getline(f12, fb))
    {
        double val = stod(cleanStr(fb));
        if (val >= th)
        {
            f = true;
            cout << "ID: " << cleanStr(fid) << " | Name: " << cleanStr(fn) << " | Balance: $" << val << endl;
        }
    }
    f12.close();

    if (!f)
        cout << "No accounts found matching the threshold." << endl;
}

void del()
{
    string id;
    bool f = false;

    cout << "\n--- Delete Account ---" << endl;
    cout << "Enter Account ID to delete: ";
    cin >> id;

    ifstream f13("accounts.txt");
    ofstream f14("temp.txt");

    if (!f13 || !f14)
    {
        cout << "Error processing request!" << endl;
        return;
    }

    string fid, fn, fb;
    while (getline(f13, fid, ',') && getline(f13, fn, ',') && getline(f13, fb))
    {
        string cid = cleanStr(fid);
        if (cid == id)
        {
            f = true;
        }
        else
        {
            f14 << cid << "," << cleanStr(fn) << "," << cleanStr(fb) << endl;
        }
    }

    f13.close();
    f14.close();

    remove("accounts.txt");
    rename("temp.txt", "accounts.txt");

    if (f)
        cout << "Account with ID " << id << " deleted successfully!" << endl;
    else
        cout << "Error: Account ID not found!" << endl;
}
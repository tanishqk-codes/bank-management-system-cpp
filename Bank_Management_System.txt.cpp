#include <iostream>
#include <fstream>

using namespace std;

class BankAccount
{
public:
    string name;
    int accountNumber;
    int age;
    string phoneNumber;
    float balance;
    string lastTransaction;
};

BankAccount accounts[100];

int totalAccounts = 0;
void saveToFile();
void loadFromFile();
// =====================================
// LOGIN SYSTEM
// =====================================

bool login()
{
    string username;
    string password;

    cout << "\n========== BANK LOGIN ==========\n";

    cout << "Enter Username: ";
    cin >> username;

    cout << "Enter Password: ";
    cin >> password;

    if (username == "admin" &&
        password == "1234")
    {
        cout << "\nLogin Successful!\n";

        return true;
    }

    else
    {
        cout << "\nInvalid Username or Password!\n";

        return false;
    }
}
// =====================================
// CREATE ACCOUNT FUNCTION
// =====================================

void createAccount()
{
    cout << "\nEnter Account Holder Name: ";

    cin.ignore();

    getline(cin, accounts[totalAccounts].name);

    cout << "Enter Account Number: ";
    cin >> accounts[totalAccounts].accountNumber;

    // CHECK DUPLICATE ACCOUNT NUMBER

    for (int i = 0; i < totalAccounts; i++)
    {
        if (accounts[i].accountNumber ==
            accounts[totalAccounts].accountNumber)
        {
            cout << "\nAccount Number Already Exists!\n";

            return;
        }
    }

    cout << "Enter Age: ";
    cin >> accounts[totalAccounts].age;

    cout << "Enter Phone Number: ";
    cin >> accounts[totalAccounts].phoneNumber;

    cout << "Enter Initial Balance: ";
    cin >> accounts[totalAccounts].balance;
    
    accounts[totalAccounts].lastTransaction =
    "Account Created";
    
    totalAccounts++;
    saveToFile();

    cout << "\nAccount Created Successfully!\n";
}
   // =====================================
// SHOW ALL ACCOUNTS
// =====================================

void showAccounts()
{
    if (totalAccounts == 0)
    {
        cout << "\nNo Accounts Found.\n";
        return;
    }
    

    cout << "\n====================================\n";
    cout << "         ALL ACCOUNTS\n";
    cout << "====================================\n";

    for (int i = 0; i < totalAccounts; i++)
    {
        cout << "\n------------------------------------\n";
        cout << "Account " << i + 1 << endl;
        cout << "------------------------------------\n";

        cout << "Name: " << accounts[i].name << endl;
        cout << "Account Number: " << accounts[i].accountNumber << endl;
        cout << "Age: " << accounts[i].age << endl;
        cout << "Phone Number: " << accounts[i].phoneNumber << endl;
        cout << "Balance: " << accounts[i].balance << endl;
        cout << "Last Transaction: "
             << accounts[i].lastTransaction << endl;
    }
}

// =====================================
// SEARCH ACCOUNT FUNCTION
// =====================================

void searchAccount()
{
    if (totalAccounts == 0)
    {
        cout << "\nNo Accounts Found.\n";
        return;
    }

    int accountNo;

    cout << "\nEnter Account Number to Search: ";
    cin >> accountNo;

    bool found = false;

    for (int i = 0; i < totalAccounts; i++)
    {
        if (accounts[i].accountNumber == accountNo)
        {
            found = true;

            cout << "\n====================================\n";
            cout << "         ACCOUNT FOUND\n";
            cout << "====================================\n";

            cout << "Name: "
                 << accounts[i].name << endl;

            cout << "Account Number: "
                 << accounts[i].accountNumber << endl;

            cout << "Age: "
                 << accounts[i].age << endl;

            cout << "Phone Number: "
                 << accounts[i].phoneNumber << endl;

            cout << "Balance: ₹"
                 << accounts[i].balance << endl;

            break;
        }
    }

    if (!found)
    {
        cout << "\nAccount Not Found.\n";
    }
}

// =====================================
// DEPOSIT MONEY FUNCTION
// =====================================

void depositMoney()
{
    if (totalAccounts == 0)
    {
        cout << "\nNo Accounts Found.\n";
        return;
    }

    int accountNo;
    float amount;

    cout << "\nEnter Account Number: ";
    cin >> accountNo;

    bool found = false;

    for (int i = 0; i < totalAccounts; i++)
    {
        if (accounts[i].accountNumber == accountNo)
        {
            found = true;

            cout << "Enter Deposit Amount: ₹";
            cin >> amount;

            accounts[i].balance =
            accounts[i].balance + amount;
            accounts[i].lastTransaction =
            "Money Deposited";
            
            saveToFile();

            cout << "\nMoney Deposited Successfully!\n";

            cout << "Updated Balance: ₹"
                 << accounts[i].balance << endl;

            break;
        }
    }

    if (!found)
    {
        cout << "\nAccount Not Found.\n";
    }
}

// =====================================
// SAVE TO FILE FUNCTION
// =====================================

void saveToFile()
{
    ofstream file("accounts.txt");

    for (int i = 0; i < totalAccounts; i++)
    {
        file << accounts[i].name << endl;

        file << accounts[i].accountNumber << endl;

        file << accounts[i].age << endl;

        file << accounts[i].phoneNumber << endl;

        file << accounts[i].balance << endl;
        
        file << accounts[i].lastTransaction << endl;
        
    }

    file.close();
}

// =====================================
// LOAD FROM FILE FUNCTION
// =====================================

void loadFromFile()
{
    ifstream file("accounts.txt");

    while (getline(file, accounts[totalAccounts].name))
    {
        file >> accounts[totalAccounts].accountNumber;

        file >> accounts[totalAccounts].age;

        file >> accounts[totalAccounts].phoneNumber;

        file >> accounts[totalAccounts].balance;

        file.ignore();

        getline(file,
        accounts[totalAccounts].lastTransaction);

        totalAccounts++;
    }

    file.close();
}
    
// =====================================
// WITHDRAW MONEY FUNCTION
// =====================================

void withdrawMoney()
{
    if (totalAccounts == 0)
    {
        cout << "\nNo Accounts Found.\n";
        return;
    }

    int accountNo;
    float amount;

    cout << "\nEnter Account Number: ";
    cin >> accountNo;

    bool found = false;

    for (int i = 0; i < totalAccounts; i++)
    {
        if (accounts[i].accountNumber == accountNo)
        {
            found = true;

            cout << "Enter Withdraw Amount: ₹";
            cin >> amount;

            if (amount > accounts[i].balance)
            {
                cout << "\nInsufficient Balance!\n";
            }

            else
            {
                accounts[i].balance =
                accounts[i].balance - amount;
                accounts[i].lastTransaction =
                "Money Withdrawn";

                saveToFile();

                cout << "\nMoney Withdrawn Successfully!\n";

                cout << "Remaining Balance: ₹"
                << accounts[i].balance << endl;
            }

            break;
        }
    }

    if (!found)
    {
        cout << "\nAccount Not Found.\n";
    }
}

// =====================================
// TRANSFER MONEY FUNCTION
// =====================================

void transferMoney()
{
    if (totalAccounts < 2)
    {
        cout << "\nAt Least Two Accounts Required.\n";
        return;
    }

    int senderAcc;
    int receiverAcc;
    float amount;

    cout << "\nEnter Sender Account Number: ";
    cin >> senderAcc;

    cout << "Enter Receiver Account Number: ";
    cin >> receiverAcc;

    if (senderAcc == receiverAcc)
    {
        cout << "\nCannot Transfer To Same Account!\n";
        return;
    }

    cout << "Enter Transfer Amount: ₹";
    cin >> amount;

    int senderIndex = -1;
    int receiverIndex = -1;

    for (int i = 0; i < totalAccounts; i++)
    {
        if (accounts[i].accountNumber == senderAcc)
        {
            senderIndex = i;
        }

        if (accounts[i].accountNumber == receiverAcc)
        {
            receiverIndex = i;
        }
    }

    if (senderIndex == -1 || receiverIndex == -1)
    {
        cout << "\nInvalid Account Number!\n";
        return;
    }

    if (amount > accounts[senderIndex].balance)
    {
        cout << "\nInsufficient Balance!\n";
        return;
    }

    accounts[senderIndex].balance =
    accounts[senderIndex].balance - amount;

    accounts[receiverIndex].balance =
    accounts[receiverIndex].balance + amount;

    accounts[senderIndex].lastTransaction =
    "Money Transferred";

    accounts[receiverIndex].lastTransaction =
    "Money Received";

    saveToFile();

    cout << "\nMoney Transfer Successful!\n";

    cout << "\nSender Remaining Balance: ₹"
         << accounts[senderIndex].balance << endl;
}

// =====================================
// SHOW STATISTICS FUNCTION
// =====================================

void showStatistics()
{
    if (totalAccounts == 0)
    {
        cout << "\nNo Accounts Found.\n";
        return;
    }

    float totalBalance = 0;

    int richestIndex = 0;
    int lowestIndex = 0;

    for (int i = 0; i < totalAccounts; i++)
    {
        totalBalance =
        totalBalance + accounts[i].balance;

        if (accounts[i].balance >
            accounts[richestIndex].balance)
        {
            richestIndex = i;
        }

        if (accounts[i].balance <
            accounts[lowestIndex].balance)
        {
            lowestIndex = i;
        }
    }

    float averageBalance =
    totalBalance / totalAccounts;

    cout << "\n====================================\n";
    cout << "         BANK STATISTICS\n";
    cout << "====================================\n";

    cout << "Total Accounts      : "
         << totalAccounts << endl;

    cout << "Total Bank Balance  : ₹"
         << totalBalance << endl;

    cout << "Average Balance     : ₹"
         << averageBalance << endl;

    cout << "\nRichest Account Holder : "
         << accounts[richestIndex].name << endl;

    cout << "Richest Balance        : ₹"
         << accounts[richestIndex].balance << endl;

    cout << "\nLowest Balance Holder : "
         << accounts[lowestIndex].name << endl;

    cout << "Lowest Balance        : ₹"
         << accounts[lowestIndex].balance << endl;

    cout << "====================================\n";
}
    
// =====================================
// SEARCH BY NAME FUNCTION
// =====================================

void searchByName()
{
    if (totalAccounts == 0)
    {
        cout << "\nNo Accounts Found.\n";
        return;
    }

    string searchName;

    cout << "\nEnter Account Holder Name: ";

    cin.ignore();

    getline(cin, searchName);

    bool found = false;

    for (int i = 0; i < totalAccounts; i++)
    {
        if (accounts[i].name == searchName)
        {
            found = true;

            cout << "\n====================================\n";
            cout << "         ACCOUNT FOUND\n";
            cout << "====================================\n";

            cout << "Name: "
                 << accounts[i].name << endl;

            cout << "Account Number: "
                 << accounts[i].accountNumber << endl;

            cout << "Age: "
                 << accounts[i].age << endl;

            cout << "Phone Number: "
                 << accounts[i].phoneNumber << endl;

            cout << "Balance: ₹"
                 << accounts[i].balance << endl;

            break;
        }
    }

    if (!found)
    {
        cout << "\nAccount Not Found.\n";
    }
}

// =====================================
// UPDATE ACCOUNT FUNCTION
// =====================================

void updateAccount()
{
    if (totalAccounts == 0)
    {
        cout << "\nNo Accounts Found.\n";
        return;
    }

    int accountNo;

    cout << "\nEnter Account Number to Update: ";
    cin >> accountNo;

    bool found = false;

    for (int i = 0; i < totalAccounts; i++)
    {
        if (accounts[i].accountNumber == accountNo)
        {
            found = true;

            cout << "\nEnter New Name: ";

            cin.ignore();

            getline(cin, accounts[i].name);

            cout << "Enter New Age: ";
            cin >> accounts[i].age;

            cout << "Enter New Phone Number: ";
            cin >> accounts[i].phoneNumber;

            saveToFile();

            cout << "\nAccount Updated Successfully!\n";

            break;
        }
    }

    if (!found)
    {
        cout << "\nAccount Not Found.\n";
    }
}

// =====================================
// DELETE ACCOUNT FUNCTION
// =====================================

void deleteAccount()
{
    if (totalAccounts == 0)
    {
        cout << "\nNo Accounts Found.\n";
        return;
    }

    int accountNo;

    cout << "\nEnter Account Number to Delete: ";
    cin >> accountNo;

    bool found = false;

    for (int i = 0; i < totalAccounts; i++)
    {
        if (accounts[i].accountNumber == accountNo)
        {
            found = true;

            for (int j = i; j < totalAccounts - 1; j++)
            {
                accounts[j] = accounts[j + 1];
            }

            totalAccounts--;

            saveToFile();

            cout << "\nAccount Deleted Successfully!\n";

            break;
        }
    }

    if (!found)
    {
        cout << "\nAccount Not Found.\n";
    }
}

// =====================================
// GENERATE ACCOUNT STATEMENT
// =====================================

void generateStatement()
{
    if (totalAccounts == 0)
    {
        cout << "\nNo Accounts Found.\n";
        return;
    }

    int accountNo;

    cout << "\nEnter Account Number: ";
    cin >> accountNo;

    bool found = false;

    for (int i = 0; i < totalAccounts; i++)
    {
        if (accounts[i].accountNumber == accountNo)
        {
            found = true;

            cout << "\n====================================\n";
            cout << "          BANK STATEMENT\n";
            cout << "====================================\n";

            cout << "Bank Name      : National Bank\n";

            cout << "Account Holder : "
                 << accounts[i].name << endl;

            cout << "Account Number : "
                 << accounts[i].accountNumber << endl;

            cout << "Age            : "
                 << accounts[i].age << endl;

            cout << "Phone Number   : "
                 << accounts[i].phoneNumber << endl;

            cout << "Current Balance: ₹"
                 << accounts[i].balance << endl;

            cout << "Account Status : Active\n";
            
            cout << "Last Transaction : "
                 << accounts[i].lastTransaction << endl;

            cout << "====================================\n";

            break;
        }
    }

    if (!found)
    {
        cout << "\nAccount Not Found.\n";
    }
}

// =====================================
// VIEW TRANSACTION FUNCTION
// =====================================

void viewTransaction()
{
    if (totalAccounts == 0)
    {
        cout << "\nNo Accounts Found.\n";
        return;
    }

    int accountNo;

    cout << "\nEnter Account Number: ";
    cin >> accountNo;

    bool found = false;

    for (int i = 0; i < totalAccounts; i++)
    {
        if (accounts[i].accountNumber == accountNo)
        {
            found = true;

            cout << "\n====================================\n";
            cout << "      TRANSACTION DETAILS\n";
            cout << "====================================\n";

            cout << "Account Holder : "
                 << accounts[i].name << endl;

            cout << "Account Number : "
                 << accounts[i].accountNumber << endl;

            cout << "Current Balance: ₹"
                 << accounts[i].balance << endl;

            cout << "Last Transaction : "
                 << accounts[i].lastTransaction << endl;

            break;
        }
    }

    if (!found)
    {
        cout << "\nAccount Not Found.\n";
    }
}

// =====================================
// MAIN FUNCTION
// =====================================

int main()
{
    if (!login())
    {
        return 0;
    }

    loadFromFile();

    cout << "\n====================================\n";
    cout << "      BANK MANAGEMENT SYSTEM\n";
    cout << "====================================\n";

    cout << "Developer : Tanishq Katiyar\n";
    cout << "Language  : C++\n";

    cout << "====================================\n";

    int choice;

    while (true)
    {
        cout << "\n=========== MAIN MENU ===========\n";

        cout << "1.Create Account\n";
        cout << "2.Show All Accounts\n";
        cout << "3.Search Account\n";
        cout << "4.Search By Name\n";
        cout << "5.Deposit Money\n";
        cout << "6.Withdraw Money\n";
        cout << "7.Update Account\n";
        cout << "8.Delete Account\n";
        cout << "9.Generate Statement\n";
        cout << "10.View Transaction History\n";
        cout << "11.Transfer Money\n";
        cout << "12.Show Statistics\n";
        cout << "13.Exit\n";

        cout << "=================================\n";

        cout << "Enter Your Choice: ";
        cin >> choice;

        if (choice == 1)
        {
            createAccount();
        }

        else if (choice == 2)
        {
            showAccounts();
        }

        else if (choice == 3)
        {
            searchAccount();
        }

        else if (choice == 4)
        {
            searchByName();
        }

        else if (choice == 5)
        {
            depositMoney();
        }

        else if (choice == 6)
        {
            withdrawMoney();
        }

        else if (choice == 7)
        {
            updateAccount();
        }

        else if (choice == 8)
        {
            deleteAccount();
        }

        else if (choice == 9)
        {
            generateStatement();
        }

        else if (choice == 10)
        {
            viewTransaction();
        }

        else if (choice == 11)
        {
            transferMoney();
        }

        else if (choice == 12)
        {
            showStatistics();
        }

        else if (choice == 13)
        {
            cout << "\nThank You For Using The System!\n";
            break;
        }

        else
        {
            cout << "\nInvalid Choice!\n";
        }
    }

    return 0;
}
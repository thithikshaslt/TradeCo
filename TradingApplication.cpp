#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>
#include <vector>
#include <cctype>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
#include <sstream>
#include <unistd.h>

using namespace std;

class UserAccount
{
        private:
                int balance;
                int deposit;
                int withdrawal;
                int bitcoin;
                int dogecoin;
                int equity;
                int bitcoin_value;
                int dogecoin_value;
                int invest;
                int returnn;
                vector<pair<string,int>> transaction;
        public:
                UserAccount() : balance(20000),deposit(0),withdrawal(0),bitcoin(0),dogecoin(0),equity(100),bitcoin_value(1000),dogecoin_value(500),invest(0),returnn(0){}
                void getAccountDetails();
                void depositMoney(int);
                void withdrawMoney(int);
                int buy(int choice);
                bool sell(int choice);
                void transactionHistory();
                void writeToFile(UserAccount&);
                void readFromFile(UserAccount&);

};
void UserAccount :: getAccountDetails()
{
        cout << "Your balance is:" << balance << endl
             << "Bitcoins:" << bitcoin << endl
             << "Dogecoins:" << dogecoin << endl
             << "Equity:" << equity << endl;
}

void UserAccount :: depositMoney(int amount)
{
        deposit += amount;
        balance += amount;
        transaction.push_back({"Deposit:",amount});
}
void UserAccount :: withdrawMoney(int amount)
{
        if(amount > balance)
        {
                cout << "Preferred withdrawal amount is greater than balance!!" << endl;
        }
        else
        {
                withdrawal += amount;
                balance -= amount;
                transaction.push_back({"Withdraw:",amount});
        }
}
int UserAccount :: buy(int choice)
{
        if(equity != 0)
        {
                srand(time(NULL));
                int luck = rand();
                if(luck % 2 == 0)
                {
                        if(choice == 1)
                        {
                                if(balance >= bitcoin_value)
                                {
                                        bitcoin += 1;
                                        balance -= bitcoin_value;
                                        invest += bitcoin*bitcoin_value;
                                        transaction.push_back({"Bitcoins bought:",bitcoin_value});
                                }
                                else
                                {
                                        cout << "Balance is not enough to buy bitcoins :(" << endl;
                                        return 0;
                                }
                        }
                        else if(choice == 2)
                        {
                                if(balance >= dogecoin_value)
                                {
                                        dogecoin += 1;
                                        balance -= dogecoin_value;
                                        invest += dogecoin*dogecoin_value;
                                        transaction.push_back({"Dogecoins bought:",dogecoin_value});
                                }
                        }
                        else
                        {
                                cout << "Invalid choice." << endl;
                                exit(0);
                        }
                }
                else
                {
                        return 0;
                }
        }
        else
        {
                return 0;
        }
        return 1;
}
bool UserAccount :: sell(int choice)
{
        switch(choice)
        {
                case 1:
                if(bitcoin != 0)
                {
                        returnn += bitcoin_value;
                        balance += bitcoin_value;
                        transaction.push_back({"Bitcoins sold:",bitcoin_value});
                        bitcoin --;
                        return true;
                }
                else
                {
                        cout << " Not enough bitcoins.";
                        return false;
                }
                case 2:
                if(dogecoin != 0)
                {
                        returnn += dogecoin_value;
                        balance += dogecoin_value;
                        transaction.push_back({"Dogecoins sold:",dogecoin_value});
                        dogecoin --;
                        return true;
                }
                else
                {
                        cout << "Not enough dogecoins.";
                        return false;
                }
                default:
                cout << "Invalid choice." << endl;
        }
}
void UserAccount :: transactionHistory()
{
        int i=0;
        char ch;
        cout << "\tTRANSACTION HISTORY:" << endl;
        for (auto it:transaction)
        {
                i++;
                cout << i << "." << it.first << "--Amount:Rs." << it.second << endl;
        }
        cout << "Do you want clear all Transactions(Enter 'Y' for yes)?" << endl;
        cin >> ch;
        ch = toupper(ch);
        if(ch == 'Y')
        {
                transaction.clear();
                cout << "All Transactions have been cleared!" << endl;
                cout << "Total Transactions cleared: " << transaction.size() << endl;
        }
        else
        {
                cout << "Total Transactions done: " << transaction.size() << endl;
        }
}
/*void UserAccount :: writeToFile(UserAccount &user) {
    ofstream file;
    file.open("user_account.txt", ios::out | ios::trunc);
    file << "Balance:" << user.balance << endl
         << "Deposit:" << user.deposit << endl
         << "Withdrawal:" << user.withdrawal << endl
         << "Bitcoin:" << user.bitcoin << endl
         << "Dogecoin:" << user.dogecoin << endl
         << "Equity:" << user.equity << endl
         << "Bitcoin Value:" << user.bitcoin_value << endl
         << "Dogecoin Value:" << user.dogecoin_value << endl
         << "Investment:" << user.invest << endl
         << "Return:" << user.returnn << endl;

    for (auto it : user.transaction) {
        file << it.first << ":" << it.second << endl;
    }
    file.close();
}*/
void UserAccount::writeToFile(UserAccount& user) {
    ofstream file;
    file.open("user_account.txt", ios::out | ios::trunc);

    file << "Account Summary\n";
    file << "-------------------------------------------\n";
    file << "Balance:           " << user.balance << endl;
    file << "Deposit:           " << user.deposit << endl;
    file << "Withdrawal:        " << user.withdrawal << endl;
    file << "Bitcoin:           " << user.bitcoin << endl;
    file << "Dogecoin:          " << user.dogecoin << endl;
    file << "Equity:            " << user.equity << endl;
    file << "Bitcoin Value:     " << user.bitcoin_value << endl;
    file << "Dogecoin Value:    " << user.dogecoin_value << endl;
    file << "Investment:        " << user.invest << endl;
    file << "Return:            " << user.returnn << endl;
    file << "-------------------------------------------\n";

    file << "Transaction History\n";
    file << "-------------------------------------------\n";
    for (auto it : user.transaction) {
        file << it.first << ": " << it.second << endl;
    }
    file << "-------------------------------------------\n";

    file.close();
}
void UserAccount :: readFromFile(UserAccount &user) {
    ifstream file;
    file.open("user_account.txt", ios::in);

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string key, value;
        getline(ss, key, ':');
        getline(ss, value, ':');

        if (key == "Balance") {
            user.balance = stoi(value);
        }
        else if (key == "Deposit") {
            user.deposit = stoi(value);
        }
        else if (key == "Withdrawal") {
            user.withdrawal = stoi(value);
        }
        else if (key == "Bitcoin") {
            user.bitcoin = stoi(value);
        }
        else if (key == "Dogecoin") {
            user.dogecoin = stoi(value);
        }
        else if (key == "Equity") {
            user.equity = stoi(value);
        }
        else if (key == "Bitcoin Value") {
            user.bitcoin_value = stoi(value);
        }
        else if (key == "Dogecoin Value") {
            user.dogecoin_value = stoi(value);
        }
        else if (key == "Investment") {
            user.invest = stoi(value);
        }
        else if (key == "Return") {
            user.returnn = stoi(value);
        }
        else {
            user.transaction.push_back({key, stoi(value)});
        }
    }

    file.close();
}
int main()
{
        UserAccount user1;
        int amt,choice,ch;
        char temp;
        bool val;
        do
        {
                cout << "*******************************************************************************************************"<<endl;
                cout << "\t\t\t\t\tTRADING APPLICATION:" << endl;
                cout << "1.ACCOUNT INFORMATION RETRIEVAL." << endl;
                cout << "2.DEPOSIT MONEY." << endl;
                cout << "3.WITHDRAW MONEY." << endl;
                cout << "4.BUY CRYPTOCURRENCY." << endl;
                cout << "5.SELL CRYPTOCURRENCY." << endl;
                cout << "6.TRANSACTION HISTORY RETRIEVAL." << endl;
                cout << "7.TO SAVE ACCOUNT DETAILS TO FILE." << endl;
                cout << "8.TO READ FROM FILE." << endl;
                cout << "9.TO EXIT." << endl;
                l1:cout << "Enter your Choice:";
                cin >> choice;
                switch(choice)
                {
                        case 1:
                                user1.getAccountDetails();
                                break;
                        case 2:
                                cout << "Enter Amount to be Deposited:";
                                cin >> amt;
                                user1.depositMoney(amt);
                                break;
                        case 3:
                                cout << "Enter the Amount to be Withdrawn:";
                                cin >> amt;
                                user1.withdrawMoney(amt);
                                break;
                        case 4:
                                cout << "What do you want to buy?\nFor bitcoins enter 1,for dogecoins enter 2." << endl;
                                cout << "1.Bitcoins." << endl;
                                cout << "2.Dogecoins." << endl;
                                cout << "Enter your choice:";
                                cin >> ch;
                                        val = user1.buy(ch);
                                        if(val == 1)
                                        {
                                                cout << "Successful Transaction." << endl;
                                        }
                                        else if(val == 0)
                                        {
                                                cout << "Better Luck next time." << endl;
                                        }
                                        else
                                        {
                                                cout << "Invalid choice." << endl;
                                        }
                                        break;
                        case 5:
                                cout << "What do you want to sell?\nFor bitcoins enter 1, for dogecoins enter 2." << endl;
                                cout << "1.Bitcoins." << endl;
                                cout << "2.Dogecoins." << endl;
                                cout << "Enter your choice:";
                                cin >> ch;
                                val = user1.sell(ch);
                                if(val)
                                {
                                        cout << "Successful Transaction" << endl;
                                }
                                break;
                        case 6:
                                user1.transactionHistory();
                                break;
                        case 7:
                                break;
                        case 8:
                                break;
                        case 9:
                                cout << "Exiting in 3...2...1..." << endl;
                                sleep(3);
                                exit(0);
                        default:
                                cout << "Invalid choice.Please enter a valid choice from 1-7." << endl;
                                goto l1;
                }
                cout << "********************************************************************************************************" << endl;
                cout << "Do you want to continue(enter 'Y' for yes)?" << endl;
                cin >> temp;
                temp = toupper(temp);
        }while(temp == 'Y');
}


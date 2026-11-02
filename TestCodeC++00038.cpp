#include <iostream>
#include <stdexcept>
#include <iomanip>
#include <limits>
#include <vector>
#include <string>
using namespace std;

class Bank_account
{
    private:
        string username;
        double Balance = 0;
        vector<double> transactions;
    
    public:
        Bank_account(const string& name, double initialdeposit) : username(name), Balance(initialdeposit) 
        {
            if (initialdeposit < 0)
            {
                throw invalid_argument("You can't deposit less than 0. ");
            }
            transactions.push_back(initialdeposit);
        }
        void Deposit(double deposited)
        {
            if (deposited <= 0)
            {
                throw invalid_argument("You can't deposit 0 or less than 0.");
            }
            Balance = Balance + deposited;
            transactions.push_back(deposited);
        }
        void Withdraw(double withdrawed)
        {
            if (withdrawed <= 0)
            {
                throw invalid_argument("You can't withdraw 0 or less than 0.");
            }    
            if (withdrawed > Balance)
            {
                throw invalid_argument("You can't withdraw more than what is in the account.");
            }  
            Balance = Balance - withdrawed;
            transactions.push_back(-withdrawed);
        }
        double getbalance() const
        {
            return Balance;
        }
        const vector<double>& gettransactions() const
        {
            return transactions;
        }
        string getusername() const
        {
            return username;
        }
};

double readdouble()
{
    double value;
    if (!(cin >> value))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        throw invalid_argument("Enter ONLY numbers.");
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return value;
}
int readint(int minimum = 1, int maximum = numeric_limits<int>::max())
{
    int value;
    if (!(cin >> value))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        throw invalid_argument("Enter ONLY numbers.");
    } else if (value < minimum || value > maximum){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        throw invalid_argument("Number out of range.");
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return value;    
}
string readstring ()
{
    string value;
    getline(cin, value);
    if (value.empty())
    {
        throw invalid_argument("The username can't be empty.");
    }
    return value;    
}
void createaccounts (vector<Bank_account>& users, int numberofusers)
{
    string name;
    double initialdeposit;
    for (int i = 0; i < numberofusers; i++)
    {
        cout << "Username: ";
        name = readstring();
        cout << "Initial deposit: ";
        initialdeposit = readdouble();
        users.push_back(Bank_account(name, initialdeposit));
    }
}
void showaccounts(const vector<Bank_account>& users)
{
    cout << "Which account you want to use? \n";
    size_t times = users.size();
    for (size_t i = 0; i < times; i++)
    {
        cout << i + 1 << ". " << users[i].getusername() << '\n';
    }    
}

void execute()
{
    int choice;
    bool run = true;
    bool successful = false;
    int actualaccount;
    vector<Bank_account> Users;
    while (!successful)
    {   
        try
        {
            cout << "How many accounts you want to create? \n";
            createaccounts(Users, readint());
            showaccounts(Users);
            actualaccount = readint(1, Users.size()) - 1;
            successful = true;
        }
        catch(const exception& error)
        {
            Users.clear();
            cout << "Error. "<< error.what() << '\n';
        }  
    }
    while (run)
    {
            try
            {
                cout << "What do you want to do? \n1.Deposit. \n2.Withdraw. \n3.See balance.\n4.Track transactions. \n5.Change account.\n6. Exit. \n";
                choice = readint(1, 6);
                switch (choice)
                {
                case 1:
                    {
                        cout << "How much you want to deposit? \n";
                        Users[actualaccount].Deposit(readdouble());
                    }
                    break;
                case 2:
                    {
                        cout << "How much you want to withdraw? \n";
                        Users[actualaccount].Withdraw(readdouble());                    
                    }
                    break;  
                case 3:
                    {
                        cout << "Balance: " << Users[actualaccount].getbalance() << '\n';
                    }
                    break; 
                case 4:
                    {
                        cout << "Transactions: \n";
                        size_t times = (Users[actualaccount].gettransactions()).size();
                        for (size_t i = 0; i < times; i++)
                        {
                            cout << (Users[actualaccount].gettransactions())[i] << '\n';
                        }
                    }
                    break; 
                case 5:
                    {
                        showaccounts(Users);
                        actualaccount = readint(1, Users.size()) - 1;
                    }  
                    break;  
                case 6:
                    {
                        run = false;
                    }
                    break;
                default:
                    {
                        throw invalid_argument("Invalid option.");
                    }
                    break;
                }
            }
            catch(const exception& error)
            {
                cout << "Error. "<< error.what() << '\n';
            }   
        }
}

int main ()
{
    cout << fixed << setprecision(2);
    execute();
    cin.get();
    return 0;
}
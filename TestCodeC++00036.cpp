#include <iostream>
#include <limits>
#include <string>
#include <iomanip>
using namespace std;

struct IG //Individual Good
{
    string gn;
    double prices;
    int stock;
};

void FI (IG* goods, int ng) // FI = Fill inventory
{
    for (int i = 0; i < ng; i++)
    {
        cout << "Name of good #" << i + 1 << ": \n";
        getline(cin, goods[i].gn);
        
        while (goods[i].gn.empty())
        {
            cout << "Error. The name can't be empty. \n";
            getline(cin, goods[i].gn);
        }

        cout << "Price: \n";
        while (!(cin >> goods[i].prices) || goods[i].prices <= 0)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error. Please enter a positive number. \n";
        }
        
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        cout << "Number in Stock: \n";
        while (!(cin >> goods[i].stock) || goods[i].stock <= 0)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error. Please enter a positive number. \n";
        }
        
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}
void AP (IG* goods, double& discount, int ng) //AP = apply discount
{
    if (discount > 0.5)
    {
        discount = 0.5;
        cout << "The discount was adjusted to 50%. \n";
    }
    for (int i = 0; i < ng; i++)
    {
        goods[i].prices = goods[i].prices * (1.0 - discount);
    }
}
IG* MEG (IG* goods,int ng)//MEG = most expensive good
{
    IG* a = goods;
    for (int i = 0; i < ng; i++)
    {
        if ((goods + i)->prices > a->prices)
        {
            a = goods + i;
        }
    }
    return a;
}
void EC (IG& a,IG& b) //EC = ExChange
{
    IG t = a;
    a = b;
    b = t;
}
void SG (const IG& goods) //SG = Show Goods
{
    cout << goods.gn << " cost " << goods.prices << " and we have in stock " << goods.stock << '\n';
}

int main ()
{
    cout << fixed << setprecision(2);
    int ng; //ng = number of goods
    cout << "How many goods you want to register? \n";
    while (!(cin >> ng) || ng <= 0)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Error. Please enter a positive number. \n";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    IG* goods = new IG[ng];

    FI(goods, ng);
    int choice;
    do
    {
        cout << "What do you want to do?(Enter a number to do a choice) \n1.Apply a discount to all goods. \n2.See the most expensive good. \n3.Reorder goods by lower to highest price. \n4.See the total value of the inventory. \n5.See all goods \nAny other to exit. \n";
        while (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error. Enter only a number. \n";
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        switch (choice)
        {
        case 1: 
        {
            double discount;
            cout << "Enter the discount that you want to apply(In decimal form). \n";
            while ( !(cin >> discount) || discount < 0.01)
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Enter a valid decimal number non-lower than 0.01. \n";
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            AP(goods, discount,ng);
            for (int i = 0; i < ng; i++)
            {
                cout << "The price of "<< goods[i].gn <<": " << goods[i].prices << '\n';
            }   
        }
            break;
        case 2:
        {
            IG* GME;
            GME = MEG(goods,ng);
            GME->prices = GME->prices * 1.1;
            cout << "The most expensive good is " << GME->gn << " with a price of " << GME->prices << ". \n";
        }
            break;
        case 3:
        {
            bool changed;
            for (int i = 0; i < ng - 1; i++)
            {
                changed = false;
                for (int j = 0; j < ng - 1 - i; j++)
                {
                    if ((goods + j)->prices > (goods + j + 1)->prices)
                    {
                        EC(*(goods + j), *(goods + j + 1));
                        changed = true;
                    }
                }
                if (!changed)
                {
                    break;
                }
            }
            for (int i = 0; i < ng; i++)
            {
                cout << goods[i].gn << " costs " << goods[i].prices << ". \n";
            }
        }
            break;
        case 4:
        {
            double TI; //TI = Total Inventory
            TI = 0;
            for (int i = 0; i < ng; i++)
            {
                TI += (goods[i].prices * goods[i].stock);
            }
            cout << "The total value of the inventory is " << TI << ". \n";
        }
            break;
        case 5:
        {
            for (int i = 0; i < ng; i++)
            {
                SG(goods[i]);
            }
        }
            break;
        default:
        {
            delete[] goods;
            goods = nullptr;
            return 0;
        }
            break;
        }
    } while (true);
}
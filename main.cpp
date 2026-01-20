#include<iostream>
#include<fstream>
#include<ctime>
using namespace std;
int user;
void User()
{
    std::ifstream fin("User.txt");
    fin>>user;
    fin.close();
}
void UserUpdate()
{
    std::ofstream fout("User.txt");
    fout<<user;
    fout.close();
}
string getCurrentTime()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);

    string timeStr =
        to_string(1900 + ltm->tm_year) + "-" +
        (ltm->tm_mon + 1 < 10 ? "0" : "") + to_string(ltm->tm_mon + 1) + "-" +
        (ltm->tm_mday < 10 ? "0" : "") + to_string(ltm->tm_mday) + "_" +
        (ltm->tm_hour < 10 ? "0" : "") + to_string(ltm->tm_hour) + ":" +
        (ltm->tm_min < 10 ? "0" : "") + to_string(ltm->tm_min);
    
    return timeStr;
}
class Bank
{
    private:
    string AccountHolderName;
    int AccountNumber;
    double Balance;
    int Pin;
    bool Unlock=true;
    string Type;
    string Time;
    public:
    void MainMenu();
    void Menu();
    void CreateAccount();
    void DeleteAccount();
    void RequestUnlock();
    void CreatePin();
    int CheckPin(int p);
    void OpenAccount();
    void DisplayDetail();
    void DisplayBalance();
    void DepositMoney();
    void WithdrawMoney();
    void UpdateAccount();
    void ChangeDetails();
    void TransferMoney();
    void UpdateTransactionHistory(int accno,string type,double amount,string time);
    void ShowTransactionHistory();
};
void Bank::MainMenu()
{
    int choice;
    cout<<"**********Welcome to the Bank Management System**********"<<endl;
    cout<<"1. Create New Account"<<endl;
    cout<<"2. Open Existing Account"<<endl;
    cout<<"3. Request Account Unlock"<<endl;
    cout<<"4. Show Transaction History"<<endl;
    cout<<"5. Exit"<<endl;
    cout<<"Enter your choice: ";
    cin>>choice;
    switch(choice)
    {
        case 1:
        CreateAccount();
        break;
        case 2:
        OpenAccount();
        break;
        case 3:
        RequestUnlock();
        break;
        case 4:
        ShowTransactionHistory();
        break;
        case 5:
        cout<<"Thank you for using the Bank Management System!"<<endl;
        exit(0);
        default:
        cout<<"Invalid choice! Please try again."<<endl;
        MainMenu();
    }
}
void Bank::Menu()
{
    int choice;
    cout<<"**********Account Menu**********"<<endl;
    cout<<"1. Display Account Details"<<endl;
    cout<<"2. Display Balance"<<endl;
    cout<<"3. Deposit Money"<<endl;
    cout<<"4. Withdraw Money"<<endl;
    cout<<"5. Change Account Details"<<endl;
    cout<<"6. Transfer Money"<<endl;
    cout<<"7. Delete Account"<<endl;
    cout<<"8. Exit to Main Menu"<<endl;
    cout<<"Enter your choice: ";
    cin>>choice;
    switch(choice)
    {
        case 1:
        DisplayDetail();
        break;
        case 2:
        DisplayBalance();
        break;
        case 3:
        DepositMoney();
        break;
        case 4:
        WithdrawMoney();
        break;
        case 5:
        ChangeDetails();
        break;
        case 6:
        TransferMoney();
        break;
        case 7:
        DeleteAccount();
        break;
        case 8:
        MainMenu();
        break;
        default:
        cout<<"Invalid choice! Please try again."<<endl;
        Menu();
    }
}
void Bank :: CreateAccount()
{
    User();
    AccountNumber=user;
    user++;
    UserUpdate();
    cout<<"Your Account Number is: "<<AccountNumber<<endl;
    cout<<"Enter Account Holder Name:"<<endl;
    cin.ignore();
    getline(cin,AccountHolderName);
    for(int i=0;i<AccountHolderName.length();i++)
    {
        if(AccountHolderName[i]==' ')
        {
            AccountHolderName[i]='_';
        }
    }
    Balance=0.0;
    CreatePin();
    ofstream fout("Bank.txt",ios::app);
    fout<<AccountNumber<<" "<<AccountHolderName<<" "<<Balance<<" "<<Pin<<" "<<Unlock<<endl;
    fout.close();
    cout<<"Account Created Successfully!"<<endl;
    MainMenu();
}
void Bank :: DeleteAccount()
{
    int accno,p;
    string name;
    double bal;
    bool un;
    ofstream temp("Temp.txt", ios::out);
    ifstream file("Bank.txt");
    bool found=false;
    while(file>>accno>>name>>bal>>p>>un)
    {
        if(accno==AccountNumber)
        {
            found=true;
            continue; 
        }
        temp << accno << " " << name << " " << bal << " " << p << " " << un << endl;
    }
    file.close();
    temp.close();
    ofstream f("Bank.txt",ios::out);
    ifstream t("Temp.txt",ios::in);
    string s;
    while(getline(t,s))
    {
        f<<s<<endl;
    }
    f.close();
    t.close();
    cout<<"Account deleted successfully!"<<endl;
    user--;
    UserUpdate();
    MainMenu();
}
void Bank :: RequestUnlock()
{
    int accNo;
    cout<<"Enter Account Number to request unlock:"<<endl;
    cin>>accNo;
    ifstream fin("Bank.txt");
    bool found=false;
    while(fin>>AccountNumber>>AccountHolderName>>Balance>>Pin>>Unlock)
    {
        if(AccountNumber==accNo)
        {
            found=true;
            if(Unlock==true)
            {
                cout<<"Account is already unlocked."<<endl;
            }
            else
            {
                Unlock=true;
                UpdateAccount();
                cout<<"Account unlock requested successfully! Please contact the bank for further assistance."<<endl;
            }
            break;
        }
    }
    fin.close();
    if(!found)
    {
        cout<<"Invalid Account Number! Please try again."<<endl;
    }
    MainMenu();
}
void Bank :: CreatePin()
{
    cout<<"Set a 4-digit PIN for your account:"<<endl;
    int p;
    while(1)
    {
        cin>>p;
        if(p>=1000 && p<=9999)
        {
            Pin=p;
            cout<<"PIN set successfully!"<<endl;
            break;
        }
        else
        {
            cout<<"Invalid PIN! Please enter a 4-digit PIN:"<<endl;
        }
    }
}
int Bank :: CheckPin(int p)
{
    int mistake=0;
    while(p!=Pin)
    {
        cout<<"Incorrect PIN! Please try again."<<endl;
        cin>>p;
        mistake++;
        if(mistake==2)
        {
            cout<<"Too many incorrect attempts! Locking account and exiting to main menu."<<endl;
            return 0;
        }
    }
    return 1;
}
void Bank :: OpenAccount()
{
    int accNo, p;
    cout<<"Enter Account Number:"<<endl;
    cin>>accNo;
    ifstream fin("Bank.txt");
    bool found=false;
    while(fin>>AccountNumber>>AccountHolderName>>Balance>>Pin>>Unlock)
    {
        if(AccountNumber==accNo)
        {
            if(Unlock==false)
            {
                cout<<"Account is locked due to multiple incorrect PIN attempts. Please contact the bank."<<endl;
                MainMenu();
                return;
            }
            cout<<"Enter PIN:"<<endl;
            cin>>p;
            if(CheckPin(p))
            {
                found=true;
                cout<<"Login Successful!"<<endl;
                Menu();
                break;
            }
            else
            {
                Unlock=false;
                UpdateAccount();
            }
        }
    }
    fin.close();
    if(!found)
    {
        cout<<"Invalid Account Number! Please try again."<<endl;
        MainMenu();
    }
}
void Bank :: DisplayDetail()
{
    cout<<"Account Number: "<<AccountNumber<<endl;
    string name=AccountHolderName;
    for(int i=0;i<name.length();i++)
    {
        if(name[i]=='_')
        {
            name[i]=' ';
        }
    }
    cout<<"Account Holder Name: "<<name<<endl;
    cout<<"Balance: "<<Balance<<endl;
    Menu();
}
void Bank :: DisplayBalance()
{
    cout<<"Current Balance: "<<Balance<<endl;
    Menu();
}
void Bank :: DepositMoney()
{
    double amount;
    cout<<"Enter amount to deposit:"<<endl;
    cin>>amount;
    if(amount>0)
    {
        Balance+=amount;
        cout<<"Amount deposited successfully!"<<endl;
        UpdateAccount();
        Type="D";
        UpdateTransactionHistory(AccountNumber,Type,amount,getCurrentTime());
    }
    else
    {
        cout<<"Invalid amount! Please try again."<<endl;
    }
    Menu();
}
void Bank :: WithdrawMoney()
{
    double amount;
    cout<<"Enter amount to withdraw:"<<endl;
    cin>>amount;
    if(amount>0 && amount<=Balance)
    {
        Balance-=amount;
        cout<<"Amount withdrawn successfully!"<<endl;
        UpdateAccount();
        Type="W";
        UpdateTransactionHistory(AccountNumber,Type,amount,getCurrentTime());
    }
    else
    {
        cout<<"Invalid amount or insufficient balance! Please try again."<<endl;
    }
    Menu();
}
void Bank :: UpdateAccount()
{
    fstream file("Bank.txt");
    fstream temp("Temp.txt", ios::out);
    file.seekg(0, ios::beg);
    int accNo,pin;
    string name;
    double bal;
    bool un;
    while(file>>accNo>>name>>bal>>pin>>un)
    {
        if(accNo == AccountNumber)
        {
            temp << AccountNumber << " " << AccountHolderName << " " << Balance << " " << Pin << " " << Unlock << endl;
        }
        else
        {
            temp << accNo << " " << name << " " << bal << " " << pin << " " << un << endl;
        }
    }
    file.close();
    temp.close();
    int a,p;
    string n;
    double b;
    ofstream f("Bank.txt",ios::out);
    ifstream t("Temp.txt",ios::in);
    string s;
    while(getline(t,s))
    {
        f<<s<<endl;
    }
}
void Bank :: ChangeDetails()
{
    int c;
    cout<<"1. Change Account Holder Name"<<endl;
    cout<<"2. Change PIN"<<endl;
    cout<<"Enter your choice: ";
    cin>>c;
    if(c==1)
    {
        cout<<"Enter new Account Holder Name:"<<endl;
        cin.ignore();
        getline(cin,AccountHolderName);
        for(int i=0;i<AccountHolderName.length();i++)
        {
            if(AccountHolderName[i]==' ')
            {
                AccountHolderName[i]='_';
            }
        }
        UpdateAccount();
        cout<<"Account Holder Name updated successfully!"<<endl;
        Menu();
    }
    else if(c==2)
    {
        int p,newp;
        cout<<"Enter current PIN:"<<endl;
        cin>>p;
        if(p==Pin)
        {
            cout<<"Enter new 4-digit PIN:"<<endl;
            while(1)
            {
                cin>>newp;
                if(newp>=1000 && newp<=9999)
                {
                    Pin=newp;
                    UpdateAccount();
                    cout<<"PIN updated successfully!"<<endl;
                    break;
                }
                else
                {
                    cout<<"Invalid PIN! Please enter a 4-digit PIN:"<<endl;
                }
            }
        }
        else
        {
            cout<<"Incorrect current PIN! Please try again."<<endl;
        }
        Menu();
    }
    else
    {
        cout<<"Invalid choice! Please try again."<<endl;
    }
}
void Bank :: TransferMoney()
{
    Bank b1;
    int accNo;
    cout<<"Enter Account Number:"<<endl;
    cin>>accNo;
    ifstream fin("Bank.txt");
    bool found=false;
    while(fin>>b1.AccountNumber>>b1.AccountHolderName>>b1.Balance>>b1.Pin>>b1.Unlock)
    {
        if(b1.AccountNumber==accNo)
        {
            found=true;
            cout<<"Account Found!"<<endl;
            break;
        }
    }
    fin.close();
    if(!found)
    {
        cout<<"Account Not Found!"<<endl;
        Menu();
    }
    int amount;
    cout<<"Enter amount to transfer:"<<endl;
    cin>>amount;
    Balance-=amount;
    b1.Balance+=amount;
    UpdateAccount();
    b1.UpdateAccount();
    Type="T";
    b1.Type="R";
    UpdateTransactionHistory(AccountNumber,Type,amount,getCurrentTime());
    b1.UpdateTransactionHistory(b1.AccountNumber,b1.Type,amount,getCurrentTime());
    Menu();
}
void Bank :: UpdateTransactionHistory(int accno,string type,double amount,string time)
{
    ofstream fout("TransactionHistory.txt",ios::app);
    fout<<accno<<" "<<type<<" "<<amount<<" "<<time<<endl;
    fout.close();
}
void Bank :: ShowTransactionHistory()
{
    int a;
    cout<<"Enter Account Number to view transaction history:"<<endl;
    cin>>a;
    ifstream fin("TransactionHistory.txt");
    int accno;
    string type;
    double amount;
    string time;
    cout<<"Transaction History for Account Number: "<<a<<endl;
    cout<<"Type\tAmount\tTime"<<endl;
    while(fin>>accno>>type>>amount>>time)
    {
        if(accno==a)
        {
            cout<<type<<"\t"<<amount<<"\t"<<time<<endl;
        }
    }
    fin.close();
    MainMenu();
}
int main()
{
    Bank b;
    b.MainMenu();
}

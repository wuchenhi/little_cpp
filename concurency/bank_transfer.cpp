//dead lock
#include <thread>
#include <future>
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <cmath>
#include <set>

using namespace std;

//账户类
class Account {
public:
    Account(string name, double money) : mName(name), mMoney(money) {}; //要不要分号

public:
    void changeMoney(double amount){
        mMoney += amount;
    }
    string getName(){
        return mName;
    }
    double getMoney(){
        return mMoney;
    }
    mutex* getLock(){
        return &mMoneyLock;
    }

private:
    string mName;
    double mMoney;
    mutex mMoneyLock;
};

class Bank{
public:
    void addAcount(Account* account){
        mAccounts.insert(account);
    }

    bool transferMoney(Account* accountA, Account* accountB, double amount){
        lock_guard<mutex> guardA(*accountA->getLock());
        lock_guard<mutex> guardB(*accountB->getLock());
        
        if (amount > accountA->getMoney()) {
             return false;
        }
        accountA->changeMoney(-amount);
        accountB->changeMoney(amount);
        return true;
    }

    double totalMoney() const {
        double sum = 0;
        for (auto a : mAccounts) 
            sum += a->getMoney();
        return sum;
    }
private:
    set<Account* > mAccounts;
};

void randomTransfer(Bank* bank, Account* accountA, Account* accountB){
    while (1){
        double randomMoney = ((double)rand() / RAND_MAX) * 100;
        if(bank->transferMoney(accountA, accountB, randomMoney)){
            cout << "Transfer " << randomMoney << " from " << accountA->getName()
                << " to " << accountB->getName()
                << ", Bank totalMoney: " << bank->totalMoney() << endl;
        }else {
            cout << "Transfer failed, "
                 << accountA->getName() << " has only $" << accountA->getMoney() << ", but "
                 << randomMoney << " required" << endl;
        }
    }
}

int main(){
    Account a("wuyi", 100);
    Account b("yawen", 100);
    Bank myBank;
    myBank.addAcount(&a);
    myBank.addAcount(&b);

    thread t1(randomTransfer, &myBank, &a, &b);
    thread t2(randomTransfer, &myBank, &b, &a);

    t1.join();
    t2.join();

    return 0;
}
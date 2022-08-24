//dead lock
#include <thread>
#include <future>
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <cmath>
#include <set>
#include <mutex>

using namespace std;

//账户类
class Account {
public:
    Account(string name, double money) : mName(name), mMoney(money) {}; //要不要分号

public:
    void changeMoney(double amount){
        unique_lock<mutex> lock(mMoneyLock);
        mConditionVar.wait(lock, [this, amount]{   
            return mMoney + amount > 0;
        });                        //会判断lambda表达式。如果满足则继续；如果不满足，则此处会解锁互斥体，并让当前线程等待
        mMoney += amount;
        mConditionVar.notify_all();
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
    condition_variable mConditionVar;
};

class Bank{
public:
    void addAcount(Account* account){
        mAccounts.insert(account);
    }

    void transferMoney(Account* accountA, Account* accountB, double amount){
        accountA->changeMoney(-amount);
        accountB->changeMoney(amount);
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

mutex outLock; //输出加锁
void randomTransfer(Bank* bank, Account* accountA, Account* accountB){
    while (1){
        double randomMoney = ((double)rand() / RAND_MAX) * 100;
        {
        lock_guard<mutex> guard(outLock);                 //lock_guard 只在代码块里有效  所以有大括号  没有不行
        cout << "Try to Transfer " << randomMoney
           << " from " << accountA->getName() << "(" << accountA->getMoney()
           << ") to " << accountB->getName() << "(" << accountB->getMoney()
           << "), Bank totalMoney: " << bank->totalMoney() << endl;
        }
    bank->transferMoney(accountA, accountB, randomMoney);
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
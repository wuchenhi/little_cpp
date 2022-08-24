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
        
        //避免死锁
        
        //方法1
        lock(*accountA->getLock(), *accountB->getLock()); 
        lock_guard<mutex> guardA(*accountA->getLock(), adopt_lock);  //adopt_lock 假设调用方已拥有互斥的所有权
        lock_guard<mutex> guardB(*accountB->getLock(), adopt_lock);
        
        /*
        //方法2    //dead lock  why
        unique_lock<mutex> LockA(*accountA->getLock(), defer_lock);
        unique_lock<mutex> LockB(*accountB->getLock(), defer_lock);
        lock(*accountA->getLock(), *accountB->getLock()); 
         

        //方法3
        scoped_lock lockAll(*accountA->getLock(), *accountB->getLock());  //-std=c++17
        */
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

mutex outLock; //输出加锁
void randomTransfer(Bank* bank, Account* accountA, Account* accountB){
    while (1){
        double randomMoney = ((double)rand() / RAND_MAX) * 100;
        if(bank->transferMoney(accountA, accountB, randomMoney)){
            outLock.lock();
            cout << "Transfer " << randomMoney << " from " << accountA->getName()
                << " to " << accountB->getName()
                << ", Bank totalMoney: " << bank->totalMoney() << endl;
            outLock.unlock();
        }else {
            outLock.lock();
            cout << "Transfer failed, "
                 << accountA->getName() << " has only $" << accountA->getMoney() << ", but "
                 << randomMoney << " required" << endl;
            outLock.unlock();
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
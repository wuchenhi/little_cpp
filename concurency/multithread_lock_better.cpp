//right and fast
#include <thread>
#include <future>
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <cmath>
#include <mutex>

using namespace std;

static mutex m_lock;

static const int MAX = 10e8;
static double sum = 0;

void work(int min, int max){
    double tmp = 0;   //局部变量保存当前线程的处理结果
    for(int i = min; i < max; ++i){
        tmp += sqrt(i);
    }
    m_lock.lock();   //汇总总结过的时候进行锁保护
    sum += tmp;
    m_lock.unlock();

}

void concurrent_task(int min, int max){
    auto start_time =  chrono::steady_clock::now();

    unsigned concurrent_count = thread::hardware_concurrency();
    cout << "hardware_concurrency: " << concurrent_count << endl;
    vector<thread> threads;
    min = 0;
    sum = 0;
    for (int t = 0; t < concurrent_count; ++t){
        int range = max / concurrent_count * (t + 1);
        threads.push_back(thread(work, min, range));
        min = range + 1;
    }
    for (auto& t : threads){
        t.join();
    }

    auto end_time =  chrono::steady_clock::now();
    auto ms = chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count();
    cout << "Concurrent task finish, " << ms << " ms consumed, Result: " << sum << endl;
}


int main(){

    concurrent_task(0, MAX);
    
    return 0;
}
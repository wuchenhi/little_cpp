//right but too slow

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
    for(int i = min; i < max; ++i){
        m_lock.lock();  //在访问共享数据之前加锁
        sum += sqrt(i);
        m_lock.unlock();//访问完成之后解锁
    }
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
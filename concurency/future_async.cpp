#include <thread>
#include <future>
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <cmath>

using namespace std;

static const int MAX = 10e8;
static double sum = 0;

void worker(int min, int max){
    for(int i = min; i < max; ++i){
        sum += sqrt(i);
    }
}

int main(){

    double reslut = 0;
    cout << "Async task with lambda triggered, thread: " << this_thread::get_id() << endl;
    auto f1 = async(launch::async,[&reslut](){
        cout << "Lambda task in thread: " << this_thread::get_id() << endl;
        for(int i = 0; i < MAX; ++i){
            reslut += sqrt(i);
        }
    });
    cout << "Async task triggered" << endl;   //trigger  触发
    f1.wait();
    cout << "Async task finish, result: " << reslut << endl << endl;

    return 0;
}
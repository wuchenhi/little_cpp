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

class worker{
public:
    worker(int min, int max) : w_min(min), w_max(max) {}

    void work(){
        w_result = 0;
        for(int i = w_min; i < w_max; ++i){
            w_result += sqrt(i);
        }        
    }

    double getResult(){
        return w_result;
    }
private:
    int w_min;
    int w_max;
    double w_result;
};

int main(){

    worker w(0 ,MAX);
    double reslut = 0;
    cout << "Task in class triggered" << endl;

    auto f1 = async(&worker::work, &w);
    f1.wait();
    cout << "Async task finish, result: " << w.getResult()  << endl;

    return 0;
}
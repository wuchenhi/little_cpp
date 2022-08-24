#include <thread>
#include <future>
#include <iostream>

using namespace std;

//只初始化一次
void init(){
    cout << "init..." << endl;
}

void work(once_flag* flag){
    call_once(*flag, init);
}

int main(){
    once_flag flag;

    thread t1(work, &flag);
    thread t2(work, &flag);
    thread t3(work, &flag);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}
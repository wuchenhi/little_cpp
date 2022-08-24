#include <atomic>
#include <thread>
#include "assert.h"

std::atomic<bool> x,y;
std::atomic<int> z;

void write_x_then_y()
{
    x.store(true); 
    y.store(true); 
}

void read_y_then_x()
{
    while(!y.load()); //   ???
    if(x.load()) 
        ++z; 
}

int main()
{
    x=false;
    y=false;
    z=0;
    std::thread a(write_x_then_y);
    std::thread b(read_y_then_x);
    a.join();
    b.join();
    assert(z.load()!=0); 
}
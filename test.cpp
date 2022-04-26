#include <iostream>

#include "m_iterator.h"

using namespace poorstl;

template <class T> //: public iterator<random_access_iterator_tag, int, int*, int&>
class vector
{
    public:
        typedef T           value_type;
        typedef value_type* iterator;   //普通指针作为迭代器

        vector(int arg):x(arg){}
		vector(const vector& y): x(y.x){}
		~vector(){}
		vector& operator = (const vector& y){
			x = y.x;
			return *this;
		}
		
		bool operator == (const vector& T)const{return x == T.x; }
		bool operator <(const vector& T)const{ return x < T.x;}
		
		vector operator++(){
			x++;
			return *this;
		}
		vector operator++(int){
			vector I(*this);
			x++;
			return I;
		}
		vector operator--(){
			--x;
			return *this;
		}
		vector operator--(int){
			vector tmp(x);
			--x;
			return tmp;
		}
		vector operator+(int n)const{ return vector(n+x);}
		vector operator-(int n)const{return vector(n+x);}
		
		int operator[](int n)const{return x+n;}
		int operator*()const{return x;}
		
		int operator-(vector &T)const{
			return x - T.x;
		}
		int operator+(vector &T)const{
			return x + T.x;
		}
        
    // 迭代器相关操作
    iterator begin()         noexcept 
        { return begin_; }
    iterator end()           noexcept
        { return end_; }
    
    private:
        iterator begin_;  // 表示目前使用空间的头部
        iterator end_;    // 表示目前使用空间的尾部
        iterator cap_;    // 表示目前储存空间的尾部
};

int main(){
    vector<int>::iterator first1;
    vector<int>::iterator last1;
    //m_distance(first1.begin(), last1.end());
    return 0;
}
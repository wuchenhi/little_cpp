#ifndef m_VECTOR_TEST_H_
#define m_VECTOR_TEST_H_
#include <iostream>

#include "m_vector.h"

// vector test : 测试 vector 的接口与 push_back 的性能

#include <vector>

#include "m_vector.h"
//#include "test.h"

namespace poorstl
{


void vector_test()
{
  	std::cout << "[===============================================================]"<< std::endl;
  	std::cout << "[----------------- Run container test : vector -----------------]"<< std::endl;
  	std::cout << "[-------------------------- API test ---------------------------]"<< std::endl;
  	poorstl::vector<int> v1;
  	poorstl::vector<int> v2(10, 2);
  	poorstl::vector<int> v3(10, 1);
  	poorstl::vector<int> v4; //还不能=运算符，像v3这样才行
  	v3 = v2;
	std::cout << "v3(=v2)第一个元素"<< std::endl;
	std::cout << *v3.begin() << std::endl;

	std::cout << "[------------------------- 迭代器 test --------------------------]"<< std::endl;  
	std::cout << "是否为空"<< std::endl;
 	std::cout << v1.empty() << std::endl;
	std::cout << v2.empty() << std::endl;
	std::cout << v3.empty() << std::endl;
	std::cout << v4.empty() << std::endl;

	std::cout << "第一个元素"<< std::endl;
	std::cout << *v2.begin() << std::endl;
	std::cout << "第2个元素"<< std::endl;
	std::cout <<  v2[3] << std::endl;
	std::cout << "第10个元素"<< std::endl;
	std::cout <<  v2[9] << std::endl;
	std::cout << "end最后一个元素"<< std::endl;
	std::cout << *(v2.end() - 1) << std::endl;
	std::cout << "size:"<< std::endl;
	std::cout << v2.size() << std::endl;
	std::cout << "容量cap"<< std::endl;
	std::cout << v2.capacity() << std::endl;
	std::cout << "at 10个元素"<< std::endl;
	std::cout << v2.at(9)  << std::endl;
	std::cout << "back最后一个元素"<< std::endl;
	std::cout << v2.back() << std::endl;
	std::cout << "front元素"<< std::endl;
	std::cout << v2.front() << std::endl;
	std::cout << "data元素"<< std::endl;
	std::cout << *v2.data() << std::endl;

	std::cout << "[-----------------------修改容器 test ------------------------]"<< std::endl; 
	v3.clear();
	std::cout << "是否为空"<< std::endl;
	std::cout << v3.empty() << std::endl;
	v2.push_back(3);
	std::cout << "push以后最后一个元素"<< std::endl;
	std::cout << v2.back() << std::endl;
	std::cout << "size:"<< std::endl;
	std::cout << v2.size() << std::endl;
	std::cout << "容量cap"<< std::endl;
	std::cout << v2.capacity() << std::endl;

	v2.pop_back();
	std::cout << "pop以后最后一个元素"<< std::endl;
	std::cout << v2.back() << std::endl;
	std::cout << "size:"<< std::endl;
	std::cout << v2.size() << std::endl;
	std::cout << "容量cap"<< std::endl;
	std::cout << v2.capacity() << std::endl;

	v2.insert(0, 10);
	std::cout << "insert位置0以后第一个元素"<< std::endl;
	std::cout << v2.front() << std::endl;
	std::cout << v2.back() << std::endl;
	std::cout << "size:"<< std::endl;
	std::cout << v2.size() << std::endl;
	std::cout << "容量cap"<< std::endl;
	std::cout << v2.capacity() << std::endl;

}


} // namespace poorstl
#endif // m_VECTOR_TEST_H_
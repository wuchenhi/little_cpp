#ifndef M_VECTOR_TEST_H_
#define M_VECTOR_TEST_H_
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
  	poorstl::vector<int> v4;
  	//v8 = v3;
	std::cout << "是否为空"<< std::endl;
 	std::cout << v1.empty() << std::endl;
	std::cout << v2.empty() << std::endl;
	std::cout << v3.empty() << std::endl;
	std::cout << v4.empty() << std::endl;

	std::cout << "第一个元素"<< std::endl;
	std::cout << *v2.begin() << std::endl;
	std::cout << "最后一个元素"<< std::endl;
	std::cout << *v2.end() << std::endl;
	std::cout << "size:"<< std::endl;
	std::cout << v2.size() << std::endl;
	std::cout << "容量"<< std::endl;
	std::cout << v2.capacity() << std::endl;
	std::cout << "第三个元素"<< std::endl;
	std::cout << v2.at(2)  << std::endl;
	std::cout << "最后一个元素"<< std::endl;
	std::cout << v2.back() << std::endl;
	//v2.push_back(3);
	//std::cout << "push以后一个元素"<< std::endl;
	//std::cout << v2.back() << std::endl;

}


} // namespace poorstl
#endif // !M_VECTOR_TEST_H_
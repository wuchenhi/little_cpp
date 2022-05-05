#ifndef m_VECTOR_TEST_H_
#define m_VECTOR_TEST_H_
#include <iostream>

#include "m_vector.h"

// vector test : 测试 vector 的接口

#include "m_vector.h"

namespace poorstl
{

void vector_test()
{
  	std::cout << "[===============================================================]"<< std::endl;
  	std::cout << "[----------------- Run container test : vector -----------------]"<< std::endl;
  	std::cout << "[-------------------------- API test ---------------------------]"<< std::endl;
  	poorstl::vector<int> v1(10, 3);
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
	std::cout << "[-----------------------push back ------------------------]"<< std::endl; 
	v2.push_back(3);
	std::cout << "push以后最后一个元素"<< std::endl;
	std::cout << v2.back() << std::endl;
	std::cout << "size:"<< std::endl;
	std::cout << v2.size() << std::endl;
	std::cout << "容量cap"<< std::endl;
	std::cout << v2.capacity() << std::endl;
	std::cout << "[-----------------------pop back ------------------------]"<< std::endl; 
	v2.pop_back();
	std::cout << "pop以后最后一个元素"<< std::endl;
	std::cout << v2.back() << std::endl;
	std::cout << "size:"<< std::endl;
	std::cout << v2.size() << std::endl;
	std::cout << "容量cap"<< std::endl;
	std::cout << v2.capacity() << std::endl;

	std::cout << "[----------------------- insert ------------------------]"<< std::endl; 
	v2.insert(v2.begin(), 10); 
	std::cout << "insert位置0以后第一个元素"<< std::endl;
	std::cout << v2.front() << std::endl;
	std::cout << "insert位置0以后最后一个元素"<< std::endl;
	std::cout << v2.back() << std::endl;
	std::cout << "size:"<< std::endl;
	std::cout << v2.size() << std::endl;
	std::cout << "容量cap"<< std::endl;
	std::cout << v2.capacity() << std::endl;

    std::cout << "[-----------------------空间不足insert ------------------------]"<< std::endl; 
	v1.insert(v1.begin()+1, 10); 
	std::cout << "v1insert位置1以后第一个元素"<< std::endl;
	std::cout << v1.front() << std::endl;
	std::cout << "v1insert位置1以后第2个元素"<< std::endl;
	std::cout << v1[1]<< std::endl;
	std::cout << "insert位置0以后最后一个元素"<< std::endl;
	std::cout << v1.back() << std::endl;
	std::cout << "size:"<< std::endl;
	std::cout << v1.size() << std::endl;
	std::cout << "容量cap"<< std::endl;
	std::cout << v1.capacity() << std::endl;

	std::cout << "[--------------------------erase-----------------------------]"<< std::endl; 
	v2.erase(v2.begin()); 
	std::cout << "erase位置0以后第一个元素"<< std::endl;
	std::cout << v2.front() << std::endl;
	std::cout << "erase位置0以后最后一个元素"<< std::endl;
	std::cout << v2.back() << std::endl;
	std::cout << "size:"<< std::endl;
	std::cout << v2.size() << std::endl;
	std::cout << "容量cap"<< std::endl;
	std::cout << v2.capacity() << std::endl;

	std::cout << "[-----------------------resize 更小空间 ------------------------]"<< std::endl; 
    poorstl::vector<int> v5(10, 1);
	v5.resize(5);
	std::cout << "reszie以后第一个元素"<< std::endl;
	std::cout << v5.front() << std::endl;
	std::cout << "最后一个元素"<< std::endl;
	std::cout << v5.back() << std::endl;
	std::cout << "size:"<< std::endl;
	std::cout << v5.size() << std::endl;
	std::cout << "容量cap"<< std::endl;
	std::cout << v5.capacity() << std::endl;

	std::cout << "[-----------------------resize 更大空间 ------------------------]"<< std::endl; 
	v5.resize(20);
	std::cout << "reszie以后第一个元素"<< std::endl;
	std::cout << v5.front() << std::endl;
	std::cout << "reszie以后第5个元素"<< std::endl;
	std::cout << v5[4] << std::endl;
	std::cout << "reszie以后第6个元素"<< std::endl;
	std::cout << v5[5] << std::endl;
	std::cout << "最后一个元素"<< std::endl;
	std::cout << v5.back() << std::endl;
	std::cout << "size:"<< std::endl;
	std::cout << v5.size() << std::endl;
	std::cout << "容量cap"<< std::endl;
	std::cout << v5.capacity() << std::endl;

	std::cout << "[-----------------------重载运算符 ------------------------]"<< std::endl;
  	poorstl::vector<int> v6(10, 1);
  	poorstl::vector<int> v7(10, 1);
  	poorstl::vector<int> v8(10, 2);
	std::cout << "v6 == v7" << std::endl;
	std::cout << (v6 == v7) << std::endl;
	std::cout << "v6 != v7" << std::endl;
	std::cout << (v6 != v7) << std::endl;	
	std::cout << "v6 == v8" << std::endl;	
	std::cout << (v6 == v8) << std::endl;
	std::cout << "v6 != v8" << std::endl;
	std::cout << (v6 != v8) << std::endl;

	std::cout << "[-----------------------vetor<bool>-----------------------]"<< std::endl;
	//poorstl::vector<bool> v9(10, 1);  //报错


}


} // namespace poorstl
#endif // m_VECTOR_TEST_H_
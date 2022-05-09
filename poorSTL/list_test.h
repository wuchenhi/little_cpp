#ifndef m_LIST_TEST_H_
#define m_LIST_TEST_H_

#include <iostream>

#include "m_list.h"

// list test : 测试 list 的接口

namespace poorstl
{
void list_test()
{
    std::cout << "[===============================================================]" << std::endl;
    std::cout << "[------------------ Run container test : list ------------------]" << std::endl;
    std::cout << "[-------------------------- API test ---------------------------]" << std::endl;
    int a[] = { 1,2,3,4,5 };
    poorstl::list<int> l1;

    std::cout <<"l1是否爲空" <<(l1.empty()) << std::endl;
    std::cout << "l1 size=" << l1.size() << std::endl;
    //std::cout << "l1 begin=" << (*l1.begin()) << std::endl;

    for (int j = 0; j < 5; j++) {
        l1.push_back(j);
    }
    std::cout << "size=" << l1.size() << std::endl;

    list<int>::iterator ite;
    for (ite = l1.begin(); ite != l1.end(); ++ite) {
        std::cout << *ite << ' ';
    }
    std::cout << std::endl;

    poorstl::list<int> l2(5);
    std::cout <<"l2是否爲空" <<(l2.empty()) << std::endl;
    std::cout << "l2 size=" << l2.size() << std::endl;

}

}
#endif
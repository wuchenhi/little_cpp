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
    std::cout << "[------------------------ listnode test ------------------------]" << std::endl;
    poorstl::list_node<int> node1(5);

    std::cout << node1.data << std::endl;
    std::cout << node1.prev << std::endl;
    std::cout << node1.next << std::endl;
    std::cout << node1.self()->data << std::endl;
    
    std::cout << "[---------------------------- pass------------------------------]" << std::endl;

    std::cout << "[-------------------------- API test ---------------------------]" << std::endl;

    poorstl::list<int> l1;
    poorstl::list<int> l10(5, 1);
    list<int>::iterator it;
    for (it = l10.begin(); it != l10.end(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;
    std::cout <<"l1是否爲空" <<(l1.empty()) << std::endl;
    std::cout << "l1 size=" << l1.size() << std::endl;
    std::cout << "l1 begin=" << (*l1.begin()) << std::endl;

    for (int j = 0; j < 5; j++) {
        l1.push_back(j);
    }
    std::cout << "l1 size=" << l1.size() << std::endl;

    for (it = l1.begin(); it != l1.end(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;

    poorstl::list<int> l3;
    for (int j = 6; j < 10; j++) {
        l3.push_back(j);
    }
    for (it = l3.begin(); it != l3.end(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;
    std::cout << "[-------------------------- l1 splice ---------------------------]" << std::endl;
    l1.splice(l1.end(), l3);
    for (it = l1.begin(); it != l1.end(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;
    std::cout << "[-------------------------- l1 reverse ---------------------------]" << std::endl;
    l1.reverse();
    for (it = l1.begin(); it != l1.end(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;
    std::cout << "[-------------------------- l1 clear ---------------------------]" << std::endl;
    l1.clear();
    std::cout <<"l1是否爲空" <<(l1.empty()) << std::endl;

    std::cout << "[-------------------------- l2 构造 ---------------------------]" << std::endl;
    poorstl::list<int> l2(6);
    std::cout <<"l2是否爲空" <<(l2.empty()) << std::endl;
    std::cout << "l2 size=" << l2.size() << std::endl;
    std::cout << "l2 begin=" << (*l2.begin()) << std::endl;
    
    std::cout << "[-------------------------- l4 merge ---------------------------]" << std::endl;
    poorstl::list<int> l4;
    for (int j = 0; j < 5; j++) {
        l4.push_back(j);
    }
    for (it = l4.begin(); it != l4.end(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;
    for (int j = 7; j < 10; j++) {
        l2.push_back(j);
    }
    l2.merge(l4);
    for (it = l2.begin(); it != l2.end(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;
    std::cout << "[---------------------------- pass------------------------------]" << std::endl;
    std::cout << "[-------------------------- l5 unique ---------------------------]" << std::endl;
    poorstl::list<int> l5;
    for (int j = 0; j < 5; j++) {
        l5.push_back(1);
    }

    for (it = l5.begin(); it != l5.end(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;
    l5.unique();
    for (it = l5.begin(); it != l5.end(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;
    std::cout << "[---------------------------- pass------------------------------]" << std::endl;
    std::cout << "[-------------------------- l6 pop_back ------------------------]" << std::endl;
    std::cout << "[-------------------------- l6 pop_front -----------------------]" << std::endl;
    poorstl::list<int> l6;
    for (int j = 0; j < 10; j++) {
        l6.push_back(j);
    }
    for (it = l6.begin(); it != l6.end(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;

    for (int j = 0; j < 3; j++) {
        l6.pop_back();
    }
    for (it = l6.begin(); it != l6.end(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;

        for (int j = 0; j < 3; j++) {
        l6.pop_front();
    }
    for (it = l6.begin(); it != l6.end(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;
    std::cout << "[------------------------ l7 operator=-- -------------------------]" << std::endl;
    for (it = l6.begin(); it != l6.end(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;
    poorstl::list<int> l7;
    for (int j = 0; j < 10; j++) {
        l7.push_back(j);
    }
    for (it = l7.begin(); it != l7.end(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;
    l6 = l7;
    for (it = l6.begin(); it != l6.end(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;

    for (it = l7.begin(); it != l7.end(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;

    std::cout << "[-------------------------- l7 remove ---------------------------]" << std::endl;
    for (it = l6.begin(); it != l6.end(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;
    l6.remove(3);
    for (it = l6.begin(); it != l6.end(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;

    std::cout << "[-------------------------- l8 复制初始化 ---------------------------]" << std::endl;
    for (it = l6.begin(); it != l6.end(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;

    poorstl::list<int> l8(l6);
    for (it = l8.begin(); it != l8.end(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;
}

}
#endif
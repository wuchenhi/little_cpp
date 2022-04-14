#ifndef PHONE_H
#define PHONE_H
#include <iostream>
#include <cstring>
#include <unordered_map>
using namespace std;

struct node {
  string name;        // 姓名
  long int number;    // 电话号码
  struct node* next;  // 下一个节点
  node(string na, long int nm) : name(na), number(nm), next(nullptr) {}
  friend ostream& operator<<(ostream& os, node* self) {
    os << "name = " << self->name << ", number = " << self->number;
    return os;
  }
};

using Phone = struct node;
/**
 * @description: 电话本管理系统
 * @param {*}
 * @return {*}
 */
class PhoneManageSystem {
 private:
  Phone *head, *tail;  // 单链表带两个节点 头与尾
  // key = number 唯一
  // value = Phone*
  // for search O(1) time space
  unordered_map<int, Phone*> phone_record;  // 电话号码唯一
 public:
  PhoneManageSystem();
  ~PhoneManageSystem();

  Phone* inputUser();
  void display();
  void create();
  void search();
  int getSize();
  void del();
};
#endif
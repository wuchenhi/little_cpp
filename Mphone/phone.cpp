#include "phone.h"


//处理输入
Phone* PhoneManageSystem::inputUser() {
    string name;
    long int phone_num;
    std::cout << "Please input name" << std::endl;
    std::cin >> name;
    std::cout << "Please input phone_num" <<std::endl;
    std::cin >> phone_num;
    Phone* NEWp = new Phone(name, phone_num);
    return NEWp;
}


 //构造
PhoneManageSystem::PhoneManageSystem() {
    head = tail =nullptr;
}


//description: 析构
PhoneManageSystem::~PhoneManageSystem() {
    Phone* h = head;
    while(h){
        Phone* hn = h->next;
        delete h;
        h = hn;
    }
}


//O(1) 创建 尾部添加电话本记录 添加同时要求用户输入数据
void PhoneManageSystem::create() {
    Phone* in = inputUser();
    if (!head && head == tail){
        head = tail = in;
    }else{
        tail->next = in;
        tail = in;
    }
    phone_record[in->number] = in;
    display();
}


//O(n) 遍历 查看当前电话本记录有哪些
void PhoneManageSystem::display() {
    Phone* h = head;
    while(h){
        std::cout << h << std::endl;
        h = h->next;
    }
}



//O(1)搜索 查找电话本中的记录
void PhoneManageSystem::search() {
    long int phone_num;
    std::cout << "Please input phone_num" << std::endl;
    std::cin >> phone_num;
    if(phone_record.count(phone_num)){
        std::cout << phone_record[phone_num] << std::endl;
    }else{
        std::cout << "Not find" << std::endl;
    }
}

 //删除 O(n) 在该函数中输入手机号 删除电话本中的记录
void PhoneManageSystem::del() {
    long int phone_num;
    std::cout << "Please input phone_num" << std::endl;
    std::cin >> phone_num;
    if(phone_record.erase(phone_num) == 0){
        std::cout << "Not find, del fail" << std::endl;
        return;
    }
    Phone* h = head, *prev = nullptr;
    if (!head && head == tail) {
        cout << "PhoneManageSystem is empty" << endl;
        return;
    }
    while (h) {
        Phone* hn = h->next;
        if (h->number == phone_num) {
            if (head == tail) {         // 只有一个节点
                head = tail = nullptr;
            } else if (head == h) {     // 删除的是head 节点
                head = hn;
            } else if (tail == h) {     // 删除的是tail 节点
                tail = prev;
                tail->next = nullptr;
            } else {                    // 删除的是head到tail中间节点
            prev->next = hn;
        }
        delete h;
        break;
        } else {
        prev = h;
        h = hn;
        }
    }
    std::cout << "already del" << std::endl;
    display();
}

//size
int PhoneManageSystem::getSize() {
    return phone_record.size();
}
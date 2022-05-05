#ifndef STRING_H
#define STRING_H
#include <cstring>
#include <iostream>

class String {
 private:
  char* data_;
  size_t size_;

 public:
  String();
  String(const char* str);                 // 构造
  String(const String& other);             // 拷贝构造
  ~String();                               // 析构
  String& operator=(const String& other);  // 拷贝赋值

  String(String&& other) noexcept;             // 移动构造
  String& operator=(String&& other) noexcept;  // 移动赋值
  char& operator[](size_t index);                    // 重载[]操作符
  bool operator==(const String& other);              // 重载==操作符
  String operator+(const String& other);
  const char* c_str() const;
  size_t length();
  friend std::ostream& operator<<(std::ostream& out, const String& str);
  friend std::istream& operator>>(std::istream& in, String& str);
 private:
  void __init(const char* str); // 分配内存
  void __clean();               // 清除内存
  void __swap(String& other);   // 交换 用于移动构造
};
#endif
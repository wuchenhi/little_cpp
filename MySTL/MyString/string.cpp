#include "string.h"

String::String():data_(nullptr), size_(0) {}
String::String(const char* str) { __init(str); }

void String::__init(const char* str)
{
    if(!str){
        size_ = 0;
        data_ = nullptr;
    }else{
        size_ = std::strlen(str);
        data_ = new char[size_ + 1];
        strncpy(this->data_, str, this->size_+1);
    }
}

void String::__clean()
{
    if(!size_ && data_ != nullptr)
    {
        delete[] data_;
    }
    size_ = 0;
}

void String::__swap(String& other)
{
    data_ = nullptr; 
    data_ = other.data_;
    size_ = other.size_;
    other.data_ = nullptr;
    other.size_ = 0;
}

//copy constructor
String::String(const String& other)
{
    std::cout << "copy constructor" << std::endl;
    __init(other.data_);
}

//Copy assignment function
String& String::operator=(const String& other)
{
    std::cout<<"copy assignment"<<std::endl;
    if(&other != this)
    {
        __clean(); 
        __init(other.data_);
    }
    return *this;
}

//move constructor
String::String(String&& other) noexcept
{
    std::cout<<"move constructor"<<std::endl;
    __clean(); 
    __swap(other);

}

//move assignment
String& String::operator=(String&& other) noexcept
{
    if(&other != this)
    {
        __clean(); 
        __swap(other);
    }
    return *this;
}

//deconstructor
String::~String()
{
    __clean();
}

//重载[]操作符
char& String::operator[](size_t index)
{
    if(index > size_)
    {
        throw std::out_of_range("Your index is out of range!");
    }
    return data_[index];
}

//重载==操作符
bool String::operator==(const String& other)
{
    if (size_ == other.size_ && !std::strcmp(data_, other.data_)) {
        return true;
    }
    return false;
}

//重载+操作符
String String::operator+(const String& other)
{
    if (other.size_==0) 
        return *this;
	else if (this->size_==0) 
        return other;
    String s;
    s.size_ = this->size_ + other.size_;
    s.data_ = new char[s.size_ + 1];
    strncpy(s.data_, this->data_, this->size_);
    strncpy(s.data_ + this->size_, other.data_, other.size_); //TODO
    s.data_[s.size_] = '\0';
    return s;
}

//返回C风格字符串
const char* String::c_str() const
{
    return data_;
}

size_t String::length()
{
    return size_;
}

std::ostream& operator<<(std::ostream& out, const String& str)
{
    if(str.data_ == nullptr){
        out << "";
    }else{
        out << str.data_;
    }
    return out;
}

std::istream& operator>>(std::istream& in, String& str)
{
    std::cout<<"Plsease input size: " <<std::endl;
    in >> str.size_;

    std::cout<<"Plsease input data: " <<std::endl;
    str.data_ = new char[str.size_ + 1];
    in >> str.data_;
    int len = strlen(str.data_);
    if(len > str.size_){
        std::cout<<"sorry! data len > size" <<std::endl;
        exit(1);
    }
    return in;
}

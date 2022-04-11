#include "string.h"

String::String():data_(nullptr), size_(0){}
String::String(const char* str) {__init(str);}

void String::__init(const char* str)
{
    if(!str){
        size_ = 0;
        data_ = nullptr;
    }else{
        size_ = std::strlen(str);
        data_ = new char[size_ + 1];
        strncpy(data_, str, size_);
        data_[size_] = '\0';
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
    data_ = nullptr; //TODO
    data_ = other.data_;
    size_ = other.size_;
    other.data_ = nullptr;
    other.size_ = 0;
}

//copy construct
String::String(const String& other)
{
    __init(other.data_);
}

String& String::operator=(const String& other)
{
    std::cout<<"copy"<<std::endl;
    if(&other != this)
    {
        __clean(); //TODO
        __init(other.data_);
    }
    return *this;
}

String::String(String&& other) noexcept //why noexcept
{
    std::cout<<"move"<<std::endl;
    __clean(); //TODO
    __swap(other);

}

String& String::operator=(String&& other) noexcept
{
    if(&other != this)
    {
        __clean(); //TODO
        __swap(other);
    }
    return *this;
}

//deconstruct
String::~String()
{
    __clean();
}

char& String::operator[](size_t index)
{
    if(index > size_)
    {
        throw std::out_of_range("Your index is out of range!");
    }
    return data_[index];
}

bool String::operator==(const String& other)
{
    //TODO
    if(other.data_ == data_)
    {
        return true;
    }
    return false;
}

//TODO
String String::operator+(const String& other)
{
    //TODO
    String s;
    s.size_ = this->size_ + other.size_;
    s.data_ = new char[s.size_+1];
    //TODO
    strncpy(s.data_, this->data_, this->size_);
    strncpy(s.data_ + this->size_, other.data_, other.size_);
    s.data_[s.size_] = '\0';
    return s;
}

const char* String::c_str() const //TODO
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
    in >> str.data_;
    int len = strlen(str.data_);
    if(len > str.size_){
        std::cout<<"sorry! data len > size" <<std::endl;
        exit(1);
    }
    return in;
}

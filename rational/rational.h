#include <iostream>

class Rational {
public:
    Rational() = default;
    Rational(int numerator, int denominator);
    ~Rational() = default;
    
    Rational operator+(Rational rhs);   // 重载加
    Rational operator-(Rational rhs);   // 重载减
    Rational operator*(Rational rhs);   // 重载乘
    Rational operator/(Rational rhs);   // 重载除
    bool operator>(Rational rhs);   // 重载>
    bool operator<(Rational rhs);   // 重载<
    void printRational();                 // 打印有理数
    
    int getNumerator() const   {return numerator_; }   // 访问分子 只读
    int getDenominator() const {return denominator_; } // 访问分母 只读
private:
    void simplifyRational();              // 有理数简化

    int numerator_;    // 分子
    int denominator_;  // 分母
};
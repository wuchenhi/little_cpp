/**
 * @file myRational.cpp
 * @author wuyi
 * @brief 有理数类 实现有理数加减乘除 比较大小
 * @date 2022-08-24
 */

#include "rational.h"

Rational::Rational(int numerator, int denominator) {
    numerator_ = numerator;
    denominator_ = denominator;

    simplifyRational();
}

void Rational::simplifyRational() {
    numerator_ = denominator_ >0 ? numerator_ : -numerator_;
    denominator_ = denominator_ >0 ? denominator_ : -denominator_;

    // 辗转相除法：除数和余数反复做除法运算，当余数为 0 时，取当前算式除数为最大公约数
    int absNumerator = abs(numerator_);
    int absDenominator = abs(denominator_);
    while(absDenominator > 0) {
        int tmp = absNumerator % absDenominator;
        absNumerator = absDenominator;
        absDenominator = tmp;
    }
    numerator_ /= absNumerator;
    denominator_ /= absNumerator;
}

Rational Rational::operator+(Rational rhs) {
    int ansNum = numerator_ * rhs.getDenominator() + denominator_ * rhs.getNumerator();
    int ansDenom = denominator_ * rhs.getDenominator();
    return Rational(ansNum, ansDenom);
}

Rational Rational::operator-(Rational rhs) {
    int ansNum = numerator_ * rhs.getDenominator() - denominator_ * rhs.getNumerator();
    int ansDenom = denominator_ * rhs.getDenominator();
    return Rational(ansNum, ansDenom);
}

Rational Rational::operator*(Rational rhs) {
    int ansNum = numerator_ * rhs.getNumerator();
    int ansDenom = denominator_ * rhs.getDenominator();
    return Rational(ansNum, ansDenom);
}

Rational Rational::operator/(Rational rhs) {
    int ansNum = numerator_ * rhs.getDenominator();
    int ansDenom = denominator_ * rhs.getNumerator();
    return Rational(ansNum, ansDenom);
}

bool Rational::operator>(Rational rhs) {
    int tmp = numerator_ * rhs.denominator_ - denominator_ * rhs.numerator_;
    return tmp > 0;
}

bool Rational::operator<(Rational rhs) {
    int tmp = numerator_ * rhs.denominator_ - denominator_ * rhs.numerator_;
    return tmp < 0;
}


void Rational::printRational() {
    if(numerator_ % denominator_ == 0) {
        std::cout << numerator_ / denominator_;
    }else {
        std::cout << numerator_ << "/" << denominator_;
    }
}
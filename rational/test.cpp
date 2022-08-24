#include "rational.h"

int main() {
    Rational r1(6, 16);
    Rational r2(20, 32);

    Rational ans = r1 + r2;
    r1.printRational();
    std::cout << " + ";
    r2.printRational();
    std::cout << " = ";
    ans.printRational();
    std::cout << std::endl;
    
    ans = r1 - r2;
    r1.printRational();
    std::cout << " - ";
    r2.printRational();
    std::cout << " = ";
    ans.printRational();
    std::cout << std::endl;

    ans = r1 * r2;
    r1.printRational();
    std::cout << " * ";
    r2.printRational();
    std::cout << " = ";
    ans.printRational();
    std::cout << std::endl;

    ans = r1 / r2;
    r1.printRational();
    std::cout << " / ";
    r2.printRational();
    std::cout << " = ";
    ans.printRational();
    std::cout << std::endl;
}
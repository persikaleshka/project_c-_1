#ifndef BIGNUMBER_H
#define BIGNUMBER_H

#include <string>
#include <iostream>

class BigNumber {
public:
    BigNumber();                            
    BigNumber(const std::string& num);      
    BigNumber(double value);                

    // Операторы арифметики
    BigNumber operator+(const BigNumber& other) const; 
    BigNumber operator-(const BigNumber& other) const; 
    BigNumber operator*(const BigNumber& other) const; 
    BigNumber operator/(const BigNumber& other) const; 

    // Операторы сравнения
    bool operator==(const BigNumber& other) const; 
    bool operator!=(const BigNumber& other) const; 
    bool operator<(const BigNumber& other) const;  
    bool operator>(const BigNumber& other) const;  
    bool operator<=(const BigNumber& other) const; 
    bool operator>=(const BigNumber& other) const; 

    std::string toString() const;

private:
    std::string integer; 
    std::string fractional; 
    bool sign; 
};

#endif 

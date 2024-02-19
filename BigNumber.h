#ifndef BIGNUMBER_H
#define BIGNUMBER_H

#include <string>
#include <iostream>

class BigNumber {
public:
    std::string integer; 
    std::string fractional; 
    bool sign; 

    BigNumber();                            
    BigNumber(const std::string& num);      
    BigNumber(double value);                

    // Операторы арифметики
    BigNumber operator - () const;
    BigNumber operator + () const;
    friend BigNumber operator + (const BigNumber& first, const BigNumber& second); 
    friend BigNumber operator - (const BigNumber& first,  const BigNumber& second); 
    friend BigNumber operator * (const BigNumber& first, const BigNumber& second); 
    friend BigNumber operator / (const BigNumber& first, const BigNumber& second); 

    // Операторы сравнения
    bool operator == (const BigNumber& other) const; 
    bool operator != (const BigNumber& other) const; 
    bool operator < (const BigNumber& other) const;  
    bool operator > (const BigNumber& other) const;  
    bool operator <= (const BigNumber& other) const; 
    bool operator >= (const BigNumber& other) const; 

    std::string toString() const;

};

// input and output
std::ostream& operator<<(std::ostream& out, const BigNumber& number);
std::istream& operator>>(std::istream& in, BigNumber& number);

#endif 

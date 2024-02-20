#ifndef BIGNUMBER_H
#define BIGNUMBER_H

#include <string>
#include <iostream>

class BigNumber {
public:
    std::string integer; 
    std::string fractional; 
    bool sign; 

    BigNumber() : integer("0"), fractional("0"), sign(false) {};

    BigNumber(const std::string& number) {
        std::string num = number;
        if (num[0] == '-') {
            sign = true;
            num = num.substr(1);
        }

        size_t pos_point = num.find('.');
        if (pos_point != std::string::npos) {
            integer = num.substr(0, pos_point);
            fractional = num.substr(pos_point + 1);
        } else {
            integer = num;
            fractional = "";
        }
    };

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
std::ostream& operator << (std::ostream& out, const BigNumber& number);
std::istream& operator >> (std::istream& in, BigNumber& number);

#endif 

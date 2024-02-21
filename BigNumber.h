#ifndef BIGNUMBER_H
#define BIGNUMBER_H

#include <string>
#include <iostream>

class BigNumber {
private:
    std::string integer; 
    std::string fractional; 
    bool sign;
public:
     
    BigNumber() : integer("0"), fractional("0"), sign(false) {};
    explicit BigNumber(int number);
    explicit BigNumber(unsigned number);
    explicit BigNumber(long long number);
    explicit BigNumber(unsigned long long number);
    explicit BigNumber(double number);
    explicit BigNumber(const std::string& number) {
        std::string num = number;
        if (num[0] == '-') {
            sign = true;
            num = num.substr(1);
        }
        else{
            sign = false;
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

    // Операторы арифметики
    BigNumber operator - () const;
    BigNumber operator + () const;
    friend BigNumber operator + (const BigNumber& first, const BigNumber& second); 
    friend BigNumber operator - (const BigNumber& first, const BigNumber& second); 
    friend BigNumber operator * (const BigNumber& first, const BigNumber& second); 
    friend BigNumber operator / (const BigNumber& first, const BigNumber& second); 

    // Операторы сравнения
    bool operator == (const BigNumber& other) const; 
    bool operator != (const BigNumber& other) const; 
    friend bool operator < (const BigNumber& first, const BigNumber& second);  
    friend bool operator > (const BigNumber& first, const BigNumber& second);  
    bool operator <= (const BigNumber& other) const; 
    bool operator >= (const BigNumber& other) const; 
    
    // input and output
    friend std::istream& operator >> (std::istream& in, BigNumber& number);
    friend std::ostream& operator << (std::ostream& out, const BigNumber& number);
};


#endif 

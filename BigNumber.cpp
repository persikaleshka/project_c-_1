#include "BigNumber.h"
#include <algorithm>

BigNumber BigNumber::operator - () const{
    BigNumber other = *this;
    other.sign = !other.sign;
    return other;
}
BigNumber BigNumber::operator + () const{
    return *this;
}

bool BigNumber::operator==(const BigNumber& other) const {
    return sign == other.sign && integer == other.integer && fractional == other.fractional;
}

bool BigNumber::operator!=(const BigNumber& other) const {
    return !(sign == other.sign && integer == other.integer && fractional == other.fractional);
}

bool BigNumber::operator<(const BigNumber& other) const {
    if (sign != other.sign){
        return sign;
    }
    if (integer != other.integer) {
        return (integer < other.integer) != sign;
    }
    
    return (fractional < other.fractional) != sign;
}

bool BigNumber::operator>(const BigNumber& other) const {
    if (sign != other.sign){
        return other.sign;
    }
    if (integer != other.integer) {
        return (integer > other.integer) != other.sign;
    }
    
    return (fractional > other.fractional) != other.sign;
}

bool BigNumber::operator<=(const BigNumber& other) const {
    if (sign != other.sign){
        return sign;
    }
    if (integer != other.integer) {
        return (integer <= other.integer) != sign;
    }
    
    return (fractional <= other.fractional) != sign;
}

bool BigNumber::operator>=(const BigNumber& other) const {
    if (sign != other.sign){
        return other.sign;
    }
    if (integer != other.integer) {
        return (integer >= other.integer) != other.sign;
    }
    
    return (fractional >= other.fractional) != other.sign;
}


std::string add_int(std::string& a, std::string& b){
    std::string result, slag;
    int len_a = a.size(), len_b = b.size();
    int r = abs(len_a - len_b);
    int ost = 0;

    if (len_a < len_b){
        for (int i = 0; i < r; i++){
            result += '0';
        }
        result += a;
        slag = b;
    }
    else{
        for (int i = 0; i < r; i++){
            result += '0';
        }
        result += b;
        slag = a;
    }
    int len = result.size();
    
    for (int i = len - 1; i >= 0; i--){
        int sum = (result[i] - '0') + (slag[i] - '0') + ost;
        result[i] = sum % 10 + '0';
        ost = sum / 10;
    }

    if (ost == 1){
        result = '1' + result;
    }

    return result;
}

BigNumber operator + (const BigNumber& first, const BigNumber& second) {
    std::string result, res_frac;
    std::string a = first.integer, b = second.integer;
    std::string res_int = add_int(a, b);
    
    std::string frac_a = first.fractional, frac_b = second.fractional;

    if(first.sign) {
        if(!second.sign) {
            return -((-first) + (-second));
        } else{
            return (second - (-first));
        }
    } else if(second.sign) return (first - (-second));

    int len_frac_a = frac_a.size(), len_frac_b = frac_b.size();
    int r = abs(len_frac_a - len_frac_b);
    int ost = 0;
    if (len_frac_a < len_frac_b){
        for (int i = 0; i < r; i++){
            frac_a += '0';
        }
        len_frac_a = len_frac_b;
    }
    else{
        for (int i = 0; i < r; i++){
            frac_b += '0';
        }
        len_frac_b = len_frac_a;
    }

    res_frac = frac_a;

    for (int i = len_frac_b - 1; i >= 0; i--){
        int sum = (res_frac[i] - '0') + (frac_b[i] - '0') + ost;
        res_frac[i] = sum % 10 + '0';
        ost = sum / 10;
    }
    std::string e = "1";
    if (ost == 1){
        res_int = add_int(res_int, e);
    }


    result += res_int + "." + res_frac;


    return BigNumber(result);
}

BigNumber operator - (const BigNumber& first, const BigNumber& second){
    BigNumber result;

    if(second.sign){
        return first + (-second);
    }
    else if(first.sign){
        return -((-first) + second);
    } 
    else if(first < second){
        return -(second - first);
    } 

    std::string f1 = first.fractional;
    std::string f2 = second.fractional;

    int len_f1 = f1.size(), len_f2 = f2.size();
    int x = abs(len_f1 - len_f2);
    if (len_f1 < len_f2){
        for (int i = 0; i < x; i++){
            f1 += '0';
        }
    }
    else{
        for (int i = 0; i < x; i++){
            f2 += '0';
        }
    }


    int borrow = 0; 
    std::string res_frac = ""; 
    for (int i = f1.length() - 1; i >= 0; --i) {
        int digit1 = f1[i] - '0';
        int digit2 = i < f2.length() ? f2[i] - '0' : 0;
        if (borrow) {
            if (digit1 == 0) {
                digit1 = 9;
            } else {
                digit1 -= 1;
                borrow = 0;
            }
        }
        if (digit1 < digit2) {
            digit1 += 10;
            borrow = 1;
        }
        res_frac = char(digit1 - digit2 + '0') + res_frac;
    }

    std::string res_int = ""; 
    std::string i1 = first.integer;
    std::string i2 = second.integer;
    int len_i1 = i1.size(), len_i2 = i2.size();
    
    for (int i = len_i1 - 1, j = len_i2 - 1; i >= 0 || j >= 0; --i, --j) {
        int digit1 = i >= 0 ? i1[i] - '0' : 0;
        int digit2 = j >= 0 ? i2[j] - '0' : 0;
        if (borrow) {
            if (digit1 == 0) {
                digit1 = 9;
            } else {
                digit1 -= 1;
                borrow = 0;
            }
        }
        if (digit1 < digit2) {
            digit1 += 10;
            borrow = 1;
        }
        res_int = char(digit1 - digit2 + '0') + res_int;
    }

    result.integer = res_int;
    result.fractional = res_frac;

    return result;
}



// Оператор вывода
std::ostream& operator << (std::ostream& out, const BigNumber& number) {
    if (number.sign) {
        out << '-';
    }
    out << number.integer;
    if (!number.fractional.empty() && number.fractional != "0") {
        out << '.' << number.fractional;
    }
    return out;
}

// Оператор ввода
std::istream& operator >> (std::istream& in, BigNumber& number) {
    std::string input;
    in >> input;

    size_t dotPos = input.find('.');
    number.sign = input[0] == '-';
    
    if (dotPos != std::string::npos) {
        number.integer = input.substr(0, dotPos);
        number.fractional = input.substr(dotPos + 1);
    } else {
        number.integer = input;
        number.fractional = "0";
    }
    
    if (number.sign) {
        number.integer = number.integer.substr(1);
    }

    return in;
}

BigNumber operator * (const BigNumber& first, const BigNumber& second){
    int len_int_1 = first.integer.length(), len_int_2 = second.integer.length();
    int len_frac_1 = first.fractional.length(), len_frac_2 = second.fractional.length();

    std::string number_1 = first.integer + first.fractional;
    std::string number_2 = second.integer + second.fractional;

    int len_frac = len_frac_1 + len_frac_2;

    std::vector<int> result(number_1.length() + number_2.length(), 0);

    for (int i = number_1.length() - 1; i >= 0; i--) {
        for (int j = number_2.length() - 1; j >= 0; j--) {
            int mul = (number_1[i] - '0') * (number_2[j] - '0');
            int sum = result[i + j + 1] + mul;
            result[i + j + 1] = sum % 10;
            result[i + j] += sum / 10;
        }
    }

    std::string res_str;
    for (int num : result) {
        if (!(res_str.empty() && num == 0)) { 
            res_str.push_back(num + '0');
        }
    }

    if (len_frac > 0) {
        res_str.insert(res_str.length() - len_frac, ".");
    }

    if (first.sign != second.sign && res_str != "0") {
        res_str.insert(0, "-");
    }

    return BigNumber(res_str);
}
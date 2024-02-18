#include "BigNumber.h"
#include <algorithm>

BigNumber::BigNumber() : integer("0"), fractional("0"), sign(false) {}

BigNumber::BigNumber(const std::string& number) {
    size_t dotPosition = number.find('.');
    sign = number[0] == '-';
    if (dotPosition != std::string::npos) {
        integer = number.substr(0, dotPosition);
        fractional = number.substr(dotPosition + 1);
    } else {
        integer = number;
        fractional = "0";
    }
    if (sign) {
        integer = integer.substr(1); // Убираем знак минус из целой части
    }
    // Удаление ведущих нулей из целой части
    integer.erase(0, std::min(integer.find_first_not_of('0'), integer.size() - 1));
}

// BigNumber::BigNumber(double value) {
//     number = std::to_string(value);
//     number.erase(number.find_last_not_of('0') + 1, std::string::npos);
//     if (number.back() == '.') {
//         number.pop_back();
//     }
// }


// Равно
bool BigNumber::operator==(const BigNumber& other) const {
    return sign == other.sign && integer == other.integer && fractional == other.fractional;
}

// Не равно
bool BigNumber::operator!=(const BigNumber& other) const {
    return !(sign == other.sign && integer == other.integer && fractional == other.fractional);
}

// Меньше
bool BigNumber::operator<(const BigNumber& other) const {
    if (sign != other.sign){
        return sign;
    }
    if (integer != other.integer) {
        return (integer < other.integer) != sign;
    }
    
    return (fractional < other.fractional) != sign;
}

// Больше
bool BigNumber::operator>(const BigNumber& other) const {
    if (sign != other.sign){
        return other.sign;
    }
    if (integer != other.integer) {
        return (integer > other.integer) != other.sign;
    }
    
    return (fractional > other.fractional) != other.sign;
}

// Меньше или равно
bool BigNumber::operator<=(const BigNumber& other) const {
    if (sign != other.sign){
        return sign;
    }
    if (integer != other.integer) {
        return (integer <= other.integer) != sign;
    }
    
    return (fractional <= other.fractional) != sign;
}

// Больше или равно
bool BigNumber::operator>=(const BigNumber& other) const {
    if (sign != other.sign){
        return other.sign;
    }
    if (integer != other.integer) {
        return (integer >= other.integer) != other.sign;
    }
    
    return (fractional >= other.fractional) != other.sign;
}


// Сложение
// BigNumber BigNumber::operator+(const BigNumber& other) const {
//     std::string result, res_frac;
//     std::string a = integer, b = other.integer;
//     std::string res_int = add_int(a, b);
    
//     std::string frac_a = fractional, frac_b = other.fractional;

//     int len_frac_a = frac_a.size(), len_frac_b = frac_b.size();
//     int r = abs(len_frac_a - len_frac_b);
//     int ost = 0;
//     if (len_frac_a < len_frac_b){
//         for (int i = 0; i < r; i++){
//             res_frac += '0';
//         }
//         res_frac = frac_a + res_frac;
//     }
//     else{
//         for (int i = 0; i < r; i++){
//             res_frac += '0';
//         }
//         res_frac = frac_b + res_frac;
//     }

//     return BigNumber(result);
// }

std::string add_int(std::string& a, std::string& b){
    std::string result;

    int len_a = a.size(), len_b = b.size();
    int r = abs(len_a - len_b);
    int ost = 0;

    if (len_a < len_b){
        for (int i = 0; i < r; i++){
            result += '0';
        }
    }
    result += a;

    for (int i = len_b - 1; i >= 0; i--){
        int sum = (result[i + r] - '0') + (b[i] - '0') + ost;
        result[i + r] = sum % 10 + '0';
        ost = sum / 10;
    }

    if (ost == 1){
        result = '1' + result;
    }

    return result;
}

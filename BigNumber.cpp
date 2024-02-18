#include "BigNumber.h"
#include <algorithm>

BigNumber::BigNumber() : number("0") {}

BigNumber::BigNumber(const std::string& num) : number(num) {}

BigNumber::BigNumber(double value) {
    number = std::to_string(value);
    number.erase(number.find_last_not_of('0') + 1, std::string::npos);
    if (number.back() == '.') {
        number.pop_back();
    }
}


// Равно
bool BigNumber::operator==(const BigNumber& other) const {
    return number == other.number;
}

// Не равно
bool BigNumber::operator!=(const BigNumber& other) const {
    return !(*this == other);
}

// Меньше
bool BigNumber::operator<(const BigNumber& other) const {
    if (number.size() != other.number.size()) {
        return number.size() < other.number.size();
    }
    return number < other.number;
}

// Больше
bool BigNumber::operator>(const BigNumber& other) const {
    if (number.size() != other.number.size()) {
        return number.size() > other.number.size();
    }
    return number > other.number;
}

// Меньше или равно
bool BigNumber::operator<=(const BigNumber& other) const {
    return !(*this > other);
}

// Больше или равно
bool BigNumber::operator>=(const BigNumber& other) const {
    return !(*this < other);
}


// Сложение
BigNumber BigNumber::operator+(const BigNumber& other) const {
    std::string result;
    std::string a = number, b = other.number;

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

    return BigNumber(result);
}

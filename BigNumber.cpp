#include "BigNumber.h"
#include <algorithm>
#include <vector>
#include <math.h>

BigNumber BigNumber::operator - () const{
    BigNumber other = *this;
    other.sign = !other.sign;
    if (other == BigNumber("-0")){
        other.sign = false;
    }
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

bool operator < (const BigNumber& first, const BigNumber& second){
    if (first.sign != second.sign){
        return first.sign;
    }
    if (first.integer.length() != second.integer.length()) {
        return (first.integer.length() < second.integer.length()) != first.sign;
    }
    if (first.integer != second.integer) {
        return (first.integer < second.integer) != first.sign;
    }
    
    return (first.fractional < second.fractional) != first.sign;
}

bool operator > (const BigNumber& first, const BigNumber& second){
    if (first.sign != second.sign){
        return second.sign;
    }
    if (first.integer.length() != second.integer.length()) {
        return (first.integer.length() > second.integer.length()) != second.sign;
    }
    if (first.integer != second.integer) {
        return (first.integer > second.integer) != second.sign;
    }
    
    return (first.fractional > second.fractional) != second.sign;
}

bool BigNumber::operator<=(const BigNumber& other) const {
    if (sign != other.sign){
        return sign;
    }
    if (integer.length() != other.integer.length()) {
        return (integer.length() < other.integer.length()) != sign;
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
    if (integer.length() != other.integer.length()) {
        return (integer.length() > other.integer.length()) != other.sign;
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
    } else if(second.sign){
        return (first - (-second));
    } 

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

    BigNumber res = BigNumber(result);
    if (res == BigNumber("-0")){
        res.sign = false;
    }
    return res;
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
    if (result == BigNumber("-0")){
        result.sign = false;
    }

    return result;
}



// Оператор вывода
std::ostream& operator << (std::ostream& out, const BigNumber& number) {
    if (number.sign) {
        out << '-';
    }
    out << number.integer;
    
    if (!number.fractional.empty() && number.fractional != "0") {
        
        int pos_back = std::min(BigNumber::precision, number.fractional.size());
        std::string frac(pos_back, '0');
        for (int i = 0; i < pos_back; i++){
            frac[i] = number.fractional[i];
        }
        while(!frac.empty() && frac.back() == '0'){
            frac.pop_back();
        }
        pos_back = std::min(BigNumber::precision, frac.length());
        if (pos_back != 0){
            out << '.';
        }
        
        for (size_t i = 0; i < pos_back; i++){
            out << frac[i];
        }
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
    // std::cout << first << " " << second << '\n';
    int len_int_1 = first.integer.length(); 
    int len_int_2 = second.integer.length();
    int len_frac_1 = first.fractional.length(); 
    int len_frac_2 = second.fractional.length();

    if(first.sign) {
        if(second.sign) {
            return (-first) * (-second);
        }
    }  

    std::string number_1 = first.integer + first.fractional;
    std::string number_2 = second.integer + second.fractional;

    int len_frac = len_frac_1 + len_frac_2;
    if (first == BigNumber("0") || second == BigNumber("0")){
        return BigNumber("0");
    }

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
        // std::cout << num;
        if (!(res_str.empty() && num == 0)) { 
            res_str.push_back(num + '0');
        }
    }
    // std::cout << res_str << '\n';
    if (res_str.length() < len_frac){ 
        res_str = std::string(len_frac - res_str.length() + 1, '0') + res_str;
    }
    if (len_frac > 0) {
        res_str.insert(res_str.length() - len_frac, ".");
    }

    if (first.sign != second.sign) {
        res_str = "-" + res_str;
    }
    BigNumber res = BigNumber(res_str);
    if (res.integer == ""){
        res.integer = "0";
    }
    if (res == BigNumber("-0")){
        res.sign = false;
    }
    return res;
}

BigNumber operator / (const BigNumber& first, const BigNumber& second) {
    if (second.integer == "0" && second.fractional == "0") {
        throw std::invalid_argument("Division by zero.");
    }
    
    if(first.sign) {
        if(second.sign) {
            return (-first) / (-second);
        }
        else{
            return -((-first) / second);
        }
    } else{
        if(second.sign) {
            return -(first / (-second));
        }
    }
    BigNumber low = BigNumber("0");
    BigNumber high = BigNumber("1" + std::string(second.fractional.size(), '0'));
    BigNumber mid;
    BigNumber eps("0.5");
    for (size_t i = 0; i < BigNumber::precision + 5; i++){
        eps = eps * BigNumber("0.1");
    }
    while ((high - low) > eps) {
        mid = (low + high) * BigNumber("0.5");
        if (mid * second < BigNumber("1")) {
            low = mid;
        } else {
            high = mid;
        }
    }
    BigNumber res = (low + eps) * first;
    if (res.integer == ""){
        res.integer = "0";
    }
    if (res == BigNumber("-0")){
        res.sign = false;
    }
    while(res.fractional.back() == '0'){
        res.fractional.pop_back();
    }
    if (res.fractional.empty()){
        res.fractional = "0";
    }
    return res;
}
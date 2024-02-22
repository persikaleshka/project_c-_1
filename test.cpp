#include "BigNumber.h"
#include <stdio.h>
#include <string>
#include <iostream>

size_t BigNumber::precision;

// tests
int main(void){
    BigNumber a = BigNumber("15");
    BigNumber b = BigNumber("3");
    assert(BigNumber("11111") + BigNumber("222") == BigNumber("11333"));
    assert(BigNumber("9999") + BigNumber("1") == BigNumber("10000"));
    assert(BigNumber("0.25") * BigNumber("0.05") == BigNumber("0.0125"));
    assert(BigNumber("0.1") - BigNumber("0.05") == BigNumber("0.05"));
    assert((BigNumber("100") > BigNumber("54")) == true);
    assert(BigNumber("-100") < BigNumber("-54") == true);
    assert(BigNumber("100") <= BigNumber("54") == false);
    assert((BigNumber("54") >= BigNumber("54")) == true);
    assert((BigNumber("1212121") == BigNumber("1212121")) == true);
    assert((BigNumber("88888") != BigNumber("88888")) == false);
    std::cout << a << " / " << b << " = " << (a / b) << '\n';
    return 0;
}
    
#include <stdio.h>
#include <string>
#include <iostream>
#include "BigNumber.h"
size_t BigNumber::precision;

int main(void){
    std::cout << "Set Pi precision: ";
    std::cin >> BigNumber::precision;
    BigNumber a = BigNumber("15");
    BigNumber b = BigNumber("3");
    assert(BigNumber("11111") + BigNumber("222") == BigNumber("11333"));
    // assert(BigNumber("1") / BigNumber("2") == BigNumber("0.5"));
    assert(BigNumber("9999") + BigNumber("1") == BigNumber("10000"));
    assert(BigNumber("0.25") * BigNumber("0.05") == BigNumber("0.0125"));
    assert(BigNumber("0.1") - BigNumber("0.05") == BigNumber("0.05"));
    assert((BigNumber("100") > BigNumber("54")) == true);
    assert(BigNumber("-100") < BigNumber("-54") == true);
    assert(BigNumber("100") <= BigNumber("54") == false);
    assert((BigNumber("54") >= BigNumber("54")) == true);
    assert((BigNumber("1212121") == BigNumber("1212121")) == true);
    assert((BigNumber("88888") != BigNumber("88888")) == false);

    std::cout << (a / b) << '\n';

    BigNumber Pi("0");
    BigNumber step_16("1");
    for(int k = 0; k < 100; k++) {
        BigNumber first(BigNumber(std::to_string(4)) / BigNumber(std::to_string(8 * k + 1)));
        BigNumber second(BigNumber(std::to_string(2)) / BigNumber(std::to_string(8 * k + 4)));
        BigNumber third(BigNumber(std::to_string(1)) / BigNumber(std::to_string(8 * k + 5)));
        BigNumber fourth(BigNumber(std::to_string(1)) / BigNumber(std::to_string(8 * k + 6)));
        Pi = Pi + (first - second - third - fourth) / step_16;
        step_16 = step_16 * BigNumber("16");
    }
    std::cout << Pi << '\n';
    return 0;
}

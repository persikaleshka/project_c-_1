#include <stdio.h>
#include <string>
#include <iostream>
#include "BigNumber.h"


int main(void){
    BigNumber a = BigNumber("100");
    BigNumber b = BigNumber("54");
    assert(BigNumber("11111") + BigNumber("222") == BigNumber("11333"));
    assert(BigNumber("9206251") / BigNumber("361") == BigNumber("25502.0803567172915791161358356475830078125"));
    assert(BigNumber("9999") + BigNumber("1") == BigNumber("10000"));
    assert(BigNumber("0.25") * BigNumber("0.05") == BigNumber("0.0125"));
    assert(BigNumber("0.1") - BigNumber("0.05") == BigNumber("0.05"));
    assert((BigNumber("100") > BigNumber("54")) == true);
    assert(BigNumber("-100") < BigNumber("-54") == true);

    // std::cout << comp1 << '\n';
    return 0;
}

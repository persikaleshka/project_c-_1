#include <stdio.h>
#include <string>
#include <iostream>
#include "BigNumber.h"


int main(void){
    BigNumber a = BigNumber("123.45");
    BigNumber b = BigNumber("11.5");
    std::cout << (a + b) << '\n';
    return 0;
}

#include <stdio.h>
#include <string>
#include <iostream>
#include "BigNumber.h"
#include <chrono>

size_t BigNumber::precision;

int main(void){
    std::cout << "Set Pi precision: ";
    auto start = std::chrono::high_resolution_clock::now();
    std::cin >> BigNumber::precision;
    BigNumber Pi("0");
    BigNumber step_16("1");
    for(int k = 0; k < BigNumber::precision + 10; k++) {
        BigNumber first(BigNumber(std::to_string(4)) / BigNumber(std::to_string(8 * k + 1)));
        BigNumber second(BigNumber(std::to_string(2)) / BigNumber(std::to_string(8 * k + 4)));
        BigNumber third(BigNumber(std::to_string(1)) / BigNumber(std::to_string(8 * k + 5)));
        BigNumber fourth(BigNumber(std::to_string(1)) / BigNumber(std::to_string(8 * k + 6)));
        Pi = Pi + (first - second - third - fourth) / step_16;
        step_16 = step_16 * BigNumber("16");
    }
    std::cout << Pi << '\n';
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> all_time = end - start;
    std::cout << "Time of working programm " << all_time.count() << '\n';
    return 0;
}

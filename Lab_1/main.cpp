#include <iostream>
#include <cmath>
#include "include/closest_pair_tonum.h"

int main(){
    int upper_limit;
    while (true)
    {
        if (!(std::cin >> upper_limit)) {
            std::cin.clear();
            std::cin.ignore();
            std::cout << "Wrong input" << std::endl;
            continue;
        }
        if (upper_limit > 0){
            break;
        }else {
            std::cin.clear();
            std::cin.ignore();
            std::cout << "The number must be greater than zero" << std::endl;
            continue;
        }
    }
    std::cout << closest_pair_tonum(upper_limit);
}
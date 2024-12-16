#include <iostream>
#include <cmath>
#include <string>
#include "../include/closest_pair_tonum.h"

std::string closest_pair_tonum(int upper_limit) {
    int m = upper_limit - 1;
    int n = upper_limit - 2;
    
    while (m > 0) {
        while (n > 0) {
            int TMP_sum = m + n;
            int TMP_sub = m - n;
            
            if (TMP_sub > 0) {
                int sqrt_sum = static_cast<int>(sqrt(TMP_sum));
                int sqrt_sub = static_cast<int>(sqrt(TMP_sub));
                

                if (sqrt_sum * sqrt_sum == TMP_sum && sqrt_sub * sqrt_sub == TMP_sub) {
                    return "(" + std::to_string(m) + ", " + std::to_string(n) + ")";
                }
            }
            --n;
        }
        --m;
        n = m - 1;
    }
    
    return ""; 
}
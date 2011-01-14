#include "stdafx.h"

int calc_inverse_func(const int k)
{
    int temp = (k * (3*k +1))/2; 
   // cout << k << " is " << temp << "\r\n";
    return temp;
}

int calc_inverse_func_kreg(const int k, int k_reg)
{
    int temp = ((k * (3*k +1))/2) * k_reg; 
   // cout << k << " is " << temp << "\r\n";
    return temp;
}

bool is_coefficient_negative(const int k)
{
    return (abs(k) % 2) == 1;
}

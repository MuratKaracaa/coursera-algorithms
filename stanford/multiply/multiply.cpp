//
//  multiply.cpp
//  stanford
//
//  Created by Murat Karaca on 10/29/24.
//

#include <cmath>
#include "multiply.h"

struct PartitionedNumber {
    mpz_class first;
    mpz_class second;
    
    PartitionedNumber(mpz_class first, mpz_class second) : first(first), second(second) {}

};

size_t getNumberOfDigits(const mpz_class& number) {
    return mpz_sizeinbase(number.get_mpz_t(), 10);
}

mpz_class intPow(mpz_class base, size_t exp) {
    mpz_class result = 1;
    for(int i = 0; i < exp; ++i) {
        result *= base;
    }
    return result;
}

PartitionedNumber getNumberPartitions(const mpz_class& number, size_t m){
    mpz_class divisor = intPow(10, m);

    mpz_class firstHalf = number / divisor;
    mpz_class secondHalf = number % divisor;

    return PartitionedNumber(firstHalf, secondHalf);
}


mpz_class multiply(const mpz_class& x, const mpz_class& y) {
    if (x == 0 || y == 0) {
        return 0;
    }

    size_t xDigits = getNumberOfDigits(x);
    size_t yDigits = getNumberOfDigits(y);
    size_t digitCount = std::max(xDigits, yDigits);
    if (digitCount<=2) {
        return x * y;
    } else {
        size_t m = digitCount / 2;

        PartitionedNumber partitionsX = getNumberPartitions(x,m);
        PartitionedNumber partitionsY = getNumberPartitions(y,m);
        
        
        mpz_class A = multiply(partitionsX.first, partitionsY.first);
        mpz_class B = multiply(partitionsX.second, partitionsY.second);
        mpz_class C = multiply(partitionsX.first + partitionsX.second, partitionsY.first + partitionsY.second);
        mpz_class D = C - A - B;

        mpz_class tenToM = intPow(10, m);
        mpz_class tenTo2M = intPow(tenToM, 2);

        return (A * tenTo2M) + (D * tenToM) + B;
    }
}

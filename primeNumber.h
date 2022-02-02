#pragma once
#include "bigint.h"
#include <iostream>
class primeNumber : protected bigint
{
public:
	primeNumber(std::string);
	bigint sqrt(bigint& num);
	bigint sqrt();
	bool testPrime(bigint&);//prototyp
};


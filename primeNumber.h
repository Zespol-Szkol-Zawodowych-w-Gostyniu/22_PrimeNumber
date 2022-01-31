#pragma once
#include "bigint.h"
class primeNumber : protected bigint
{
public:
	bigint sqrt(bigint& num);
	bool testPrime(bigint&);//prototyp
};


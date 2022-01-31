#include "primeNumber.h"
/*
bool testPrime(int n) {
	bool p = true;
	if (n < 2) p = false;
	if ((n != 2) && (n % 2 == 0)) p = false;
	if (n != 2) {//wszystkie i>2
		for (int dzielnik = 3; dzielnik < ceil(sqrt(n)); dzielnik += 2) {
			if (n % dzielnik == 0) {
				p = false;
				break;
			}
		}
	}
	if (p) return true;
	else false;
}
*/
//pierwiastek bedzie zwraca³ liczbe ca³kowit¹ najpbizsz¹ pierwiastkowi rzeczywistemu
bigint primeNumber::sqrt(bigint& num) {
	bigint p("0");
	bigint dwa("2");
	bigint y("1");
	p = num / dwa;
	bigint e("1");//dok³adnoœæ
	bigint x("0");
	x = num / dwa / dwa + y;
	//algorytm Newtona-Raphsona na obliczanie pierwiastka kwadratowego
	//zmieniony na nasze potrzeby
	while ((x - p) > e) {
		p = x;
		x = (p + num / p) / dwa;
	}
	return x;
}

bool primeNumber::testPrime(bigint& num) {
	bool p = true;
	bigint dwa("2");
	bigint zero("0");
	if (num < dwa) p = false;
	if ((num != dwa) && (num % dwa == zero)) p = false;
	//if (num != dwa) {//wszystkie i>2
	//	for (int dzielnik = 3; dzielnik < ceil(sqrt(num)); dzielnik += 2) {
	//	}
	//}
	return true;
}
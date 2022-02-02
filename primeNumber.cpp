#include "primeNumber.h"
primeNumber::primeNumber(std::string num):bigint(num) {
	
}
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
bigint primeNumber::sqrt() {
	bigint num("0");
	num.setNumber(this->number);
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
	bigint trzy("3");
	bigint dwa("2");
	bigint zero("0");
	if (num < dwa) p = false;
	if (num != dwa)
		if (num % dwa == zero) 
			p = false;
	bigint pierwiastek("0");
	pierwiastek = this->sqrt(num);
	if (num != dwa) {//wszystkie i>2
		for (bigint dzielnik = trzy; dzielnik < pierwiastek; dzielnik += dwa) {
			if (num % dzielnik == zero) {
				p = false;
				break;
			}
			std::cout << dzielnik.getNumber() << ",";
		}
	}
	return p;
}
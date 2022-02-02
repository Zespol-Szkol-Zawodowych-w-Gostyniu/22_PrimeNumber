

#include <iostream>
#include "bigint.h"
#include "primeNumber.h"
using namespace std;
int main()
{
    bigint a("775469056718041913532561611867");
    bigint b;
    primeNumber p1("775469056718041913532561611867");
    cout << p1.sqrt().getNumber() << endl;
    //b = p1.sqrt(a);
    //cout << b.getNumber() << endl;
    //cout << p1.testPrime(a) << endl;
}




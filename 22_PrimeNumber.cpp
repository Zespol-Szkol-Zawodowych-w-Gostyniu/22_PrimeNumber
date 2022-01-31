

#include <iostream>
#include "bigint.h"
#include "primeNumber.h"
using namespace std;
int main()
{
    bigint a("1234");
    bigint b;
    primeNumber p1;
    b = p1.sqrt(a);
    cout << b.getNumber() << endl;
}




#include <iostream>
#include "hasher.h"

using std::cin;
using std::cout;
using std::endl;

int main()
{
    Hasher hasher;

    hasher.hashString("test string");
    cout << hasher.getHashed() << endl;

    return 0;
}
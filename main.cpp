#include <iostream>
#include "hasher.h"

using std::cin;
using std::cout;
using std::endl;

int main(int argc, char **argv)
{
    if (argc <= 1)
        return 0;

    Hasher hasher;
    hasher.hashString(argv[1]);
    cout << argv[1] << " " << hasher.getHashed() << endl;

    return 0;
}
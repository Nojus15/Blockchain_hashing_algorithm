#include "hasher.h"

string Hasher::getHashed()
{
    return this->hash;
}

void Hasher::hashString(string stringToHash)
{
    this->hash = generateHash(10);
}

string Hasher::generateHash(int seed)
{
    srand(seed);
    std::string tmp_s;
    tmp_s.reserve(this->hashLength);

    for (int i = 0; i < this->hashLength; ++i)
    {
        tmp_s += this->hashSymbols[rand() % (this->hashSymbols.length() - 1)];
    }
    return tmp_s;
}

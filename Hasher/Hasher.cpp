#include "Hasher.h"

string Hasher::getHashed()
{
    return this->hash;
}

void Hasher::hashString(string stringToHash)
{
    if (stringToHash.empty())
        throw std::invalid_argument("No text provided");

    int seed = this->getSeed(stringToHash);
    this->hash = generateHash(seed);
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
int Hasher::getSeed(string stringToHash)
{
    int seed = 0;

    for (size_t i = 0; i < stringToHash.length(); i++)
    {
        seed += stringToHash[i] * (i + 1);
    }
    return seed;
};

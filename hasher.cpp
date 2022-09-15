#include "hasher.h"

string Hasher::getHashed()
{
    return this->hash;
}

void Hasher::hashString(string stringToHash)
{
    this->hash = stringToHash;
}

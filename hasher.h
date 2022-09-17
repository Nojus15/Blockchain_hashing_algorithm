#pragma once
#include <string>
#include <random>

using std::string;

class Hasher
{
public:
    string getHashed();
    void hashString(string stringToHash);

private:
    string hash;
    const static int hashLength = 64;
    const string hashSymbols = "0123456789abcdef";

    string generateHash(int seed);
};
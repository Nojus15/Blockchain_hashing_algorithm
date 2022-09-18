#pragma once
#include <string>
#include <random>
#include <iostream>

using std::cout;
using std::endl;
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
    int getSeed(string stringToHash);
};
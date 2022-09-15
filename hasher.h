#pragma once
#include <string>

using std::string;

class Hasher
{
public:
    string getHashed();
    void hashString(string stringToHash);

private:
    string hash;
    const static int hashLength = 64;
};
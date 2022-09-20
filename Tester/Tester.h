#pragma once
#include <string>
#include <random>
#include <iostream>
#include <map>
#include <vector>
#include <iterator>
#include "../Generator/Generator.h"
#include "../Hasher/Hasher.h"

using std::cout;
using std::endl;
using std::map;
using std::pair;
using std::string;
using std::vector;

typedef string hashVal;
typedef vector<string> originalVal;

class Tester
{
public:
    void runTests(size_t count, size_t symbolCount, string resFileName);

private:
    map<hashVal, originalVal> hashes;
    map<hashVal, originalVal> collisions;

    Generator gen;
    Hasher hasher;
    bool testCollisions(string resFileName);
    void generateStringsAndHashes(size_t count, size_t symbolCount);
};
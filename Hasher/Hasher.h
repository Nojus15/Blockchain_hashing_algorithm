#pragma once
#include <string>
#include <random>
#include <iostream>
#include <vector>
#include <bitset>
#include <sstream>

using std::bitset;
using std::cout;
using std::endl;
using std::string;
using std::stringstream;

class Hasher
{
public:
    string hashString(string stringToHash);

private:
    const static int hashLength = 64;
    const string hashSymbols = "0123456789abcdef";

    string text;
    stringstream binaryText;

    string generateHash(int seed);
    int getSeed(string stringToHash);

    void convertToBinary();
    void makeMultipleOf512();
    void makeRotations();
    string rotateRight(int posCount, string block);
    string rotateLeft(int posCount, string block);
    void modifyAddedZeros();
};
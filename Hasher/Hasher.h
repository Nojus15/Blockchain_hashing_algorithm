#pragma once
#include <string>
#include <random>
#include <iostream>
#include <vector>
#include <bitset>
#include <sstream>
#include <iomanip>
#include "../Timer/Timer.h"

using std::bitset;
using std::cout;
using std::endl;
using std::hex;
using std::string;
using std::stringstream;

class Hasher
{
public:
    string hashString(string stringToHash, bool coutTime = false);
    double getTimeTaken();

private:
    const static int hashLength = 64;
    const string hashSymbols = "0123456789abcdef";
    Timer timer;

    string text;
    string binaryTextStr;
    stringstream binaryText;
    string hash;
    double timeTaken = 0;
    size_t seed;

    size_t addedBits = 0;

    string addBinary(string b1, string b2);
    void convertToBinary();
    void makeMultipleOf512();
    void makeRotations();
    string rotateRight(int posCount, string block);
    string rotateLeft(int posCount, string block);
    string shiftRight(int posCount, string block);
    string shiftLeft(int posCount, string block);
    void modifyAddedZeros();
    void convertBinaryToHex();
    void calcSeed();
};
#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <random>
#include <string>
#include <cstring>

using std::cin;
using std::cout;
using std::endl;
using std::mt19937;
using std::string;
using std::to_string;

static const char charSet[] =
    "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!@#$%^&*()_+-=~`,./;'[]<>?:{}|\"\\*";

static std::random_device rd;
static std::mt19937 mt(rd());
static std::uniform_int_distribution<int> dist(0, strlen(charSet) - 1);

class Generator
{
public:
    void genFile(string fileName, size_t symbolCount);
};
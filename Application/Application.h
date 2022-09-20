#include <iostream>
#include "../Hasher/Hasher.h"
#include "../Generator/Generator.h"
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

enum AppMode
{
    GenFile,
    HashFile,
    HashLine
};

class Application
{
private:
    int argc;
    char **argv;
    string text;
    AppMode mode;
    Hasher hasher;

    void openFile(std::ifstream &open_f, string file_name);
    void readFile(string file_name);
    void processMode();
    void findMode();

public:
    Application(int argc, char **argv);
    void run();
};

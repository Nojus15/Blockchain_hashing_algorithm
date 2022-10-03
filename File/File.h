#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::stringstream;

class File
{
private:
    void openFile(std::ifstream &open_f, string file_name);

public:
    stringstream readFile(string file_name);
};

#include <iostream>
#include "hasher.h"
#include "generator.h"
#include <string>

using std::cin;
using std::cout;
using std::endl;

int main(int argc, char **argv)
{
    if (argc <= 1)
        return 0;

    string text;
    string mode = argv[1];

    if (mode == "-genFile")
    {
        Generator gen;
        gen.genFile(argv[2], std::atoi(argv[3]));
        return 0;
    }
    else if (mode == "-hashFile")
    {
        std::ifstream file;
        try
        {
            file.open(argv[2]);
            if (file.fail())
                throw std::invalid_argument("Klaida! Neteisingas failo pavadinimas.");
        }
        catch (const std::invalid_argument &e)
        {
            cout << e.what() << std::endl;
            return 0;
        }
        std::stringstream fileText;
        fileText << file.rdbuf();
        text = fileText.str();
    }
    else if (mode == "-hashLine")
    {
        text = argv[0];
    }
    else
    {
        cout << "Wrong mode selected" << endl;
        return 0;
    }

    Hasher hasher;
    hasher.hashString(text);
    cout << text << endl;
    cout << hasher.getHashed() << endl;

    return 0;
}
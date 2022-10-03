#include "File.h"

void File::openFile(std::ifstream &open_f, string file_name)
{
    string dir = "txt_files/" + file_name;
    open_f.open(dir);
    if (open_f.fail())
        throw std::invalid_argument("File \"" + file_name + "\" not found");
}

stringstream File::readFile(string file_name)
{
    std::ifstream file;
    openFile(file, file_name);

    std::stringstream fileText;
    fileText << file.rdbuf();
    return fileText;
}

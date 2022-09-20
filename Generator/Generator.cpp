#include "Generator.h"

void Generator::genFile(std::string fileName, size_t symbolCount)
{
    std::ofstream out_f("txt_files/" + fileName);
    out_f << this->genStringstream(symbolCount).rdbuf();
    out_f.close();
}

stringstream Generator::genStringstream(size_t symbolCount)
{
    stringstream out_ss;
    for (size_t i = 1; i <= symbolCount; i++)
    {
        out_ss << charSet[dist(mt)];
    }
    return out_ss;
}

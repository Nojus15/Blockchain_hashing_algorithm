#include "Generator.h"

void Generator::genFile(std::string fileName, size_t symbolCount)
{
    std::stringstream out_ss;
    for (size_t i = 1; i <= symbolCount; i++)
    {
        out_ss << charSet[dist(mt)];
    }
    std::ofstream out_f("txt_files/" + fileName);
    out_f << out_ss.rdbuf();
    out_f.close();
}
#include "Tester.h"

void Tester::generateStringsAndHashes(size_t count, size_t symbolCount)
{

    for (size_t i = 0; i < count; i++)
    {
        string text = gen.genStringstream(symbolCount).str();
        string hash = hasher.hashString(text);

        hashes[hash].push_back(text);
    }
}
bool Tester::testCollisions(string resFileName)
{
    for (auto &el : hashes)
    {
        if (el.second.size() > 1)
        {
            this->collisions.insert(el);
        }
    }
    cout << "Number of collisions: " << this->collisions.size() << endl;

    stringstream out_ss;

    for (auto &el : collisions)
    {
        out_ss << el.first << " " << el.second.size() << "    ";

        for (auto text : el.second)
        {
            out_ss << text << " ";
        }
        out_ss << endl;
    }

    std::ofstream out_f(resFileName);
    out_f << out_ss.rdbuf();
    out_f.close();
    return true;
};

void Tester::runTests(size_t count, size_t symbolCount, string resFileName)
{
    this->generateStringsAndHashes(count, symbolCount);
    this->testCollisions(resFileName);
}
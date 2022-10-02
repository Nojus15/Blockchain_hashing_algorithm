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
void Tester::testCollisions(string resFileName)
{
    for (auto &el : hashes)
    {
        if (el.second.size() > 1)
        {
            remove_duplicates(el.second);
            if (el.second.size() > 1)
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
};
void Tester::testSpeed(size_t symbolCount)
{
    string text = gen.genStringstream(symbolCount).str();

    timer.Start();
    for (int i = 0; i < 10; i++)
    {
        hasher.hashString(text);
    }
    double t = timer.Stop();
    cout << "Average time to hash " << symbolCount << " symbol string: " << t / 10 << "s" << endl;
}

void Tester::runCollisionTest(size_t count, size_t symbolCount, string resFileName)
{
    this->generateStringsAndHashes(count, symbolCount);
    this->testCollisions(resFileName);
}
void Tester::runSpeedTest(size_t symbolCount)
{
    this->testSpeed(symbolCount);
}
int Tester::testCollisionsByPairs(stringstream &out_ss, size_t symbolCount)
{
    int collisions = 0;
    string s1, h1;
    string s2, h2;
    for (int i = 0; i < 25000; i++)
    {
        s1 = this->gen.genStringstream(symbolCount).str();
        h1 = this->hasher.hashString(s1);

        s2 = this->gen.genStringstream(symbolCount).str();
        h2 = this->hasher.hashString(s2);

        if (s1.compare(s2) == 0)
        {
            out_ss << s1 << " " << s2 << endl;
            collisions++;
        }
    }
    return collisions;
}
void Tester::runCollisionTestByPairs(string resFileName)
{
    stringstream out_ss;
    int totalCollisions = 0;

    totalCollisions += this->testCollisionsByPairs(out_ss, 10);
    totalCollisions += this->testCollisionsByPairs(out_ss, 100);
    totalCollisions += this->testCollisionsByPairs(out_ss, 500);
    totalCollisions += this->testCollisionsByPairs(out_ss, 1000);

    cout << "Total collisions: " << totalCollisions << endl;
    std::ofstream out_f(resFileName);
    out_f << out_ss.rdbuf();
    out_f.close();
}
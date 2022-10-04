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
void Tester::testKonstitucija()
{
    stringstream textBuff = this->fileReader.readFile("konstitucija.txt");
    string textToHash = "";
    string line = "";
    size_t linesToGetPower = 1;
    size_t linesToGet = 2;
    size_t totalLines = linesToGet;
    bool buffNotEmpty = true;
    while (buffNotEmpty)
    {
        for (size_t i = 0; i < linesToGet; i++)
        {
            std::getline(textBuff, line, '\n');
            if (line.length() == 0)
            {
                totalLines -= (linesToGet - i);
                buffNotEmpty = false;
                break;
            }
            textToHash.append(line + '\n');
        }
        this->hasher.hashString(textToHash);
        cout << std::setw(10) << std::left << totalLines << " lines: " << this->hasher.getTimeTaken() << " s" << endl;
        linesToGet = std::pow(2, linesToGetPower);
        totalLines += linesToGet;
        linesToGetPower++;
    }
}

int Tester::LevenshteinDistance(string a, string b)
{
    int lengthA = a.length();
    int lengthB = b.length();

    std::vector<std::vector<int>> distances(lengthA + 1, std::vector<int>(lengthB + 1));
    for (int i = 0; i <= lengthA; i++)
    {
        distances[i][0] = i;
    };
    for (int j = 0; j <= lengthB; j++)
    {
        distances[0][j] = j;
    };

    for (int i = 1; i <= lengthA; i++)
        for (int j = 1; j <= lengthB; j++)
        {
            int cost = b[j - 1] == a[i - 1] ? 0 : 1;
            distances[i][j] = std::min(
                std::min(distances[i - 1][j] + 1, distances[i][j - 1] + 1),
                distances[i - 1][j - 1] + cost);
        }
    return distances[lengthA][lengthB];
}
double Tester::CalculateSimilarity(string source, string target)
{
    if ((source.length() == 0) || (target.length() == 0))
        return 0.0;
    if (source == target)
        return 100.0;
    int stepsToSame = LevenshteinDistance(source, target);
    return 100 - ((double)std::max(source.length(), target.length()) - (double)stepsToSame) / (double)std::max(source.length(), target.length()) * 100;
}
void Tester::testAvalanche()
{
    std::vector<AvalancheTestArr> v;
    int sCountArr[] = {10, 100, 500, 1000};
    string s1, s2, h1, h2;
    for (auto symbolCount : sCountArr)
        for (int i = 0; i < 25000; i++)
        {
            s1 = this->gen.genStringstream(symbolCount).str();
            s2 = s1;
            while (s2[symbolCount / 2] == s1[symbolCount / 2])
                s2[symbolCount / 2] = this->gen.genStringstream(1).str()[0];
            h1 = this->hasher.hashString(s1);
            h2 = this->hasher.hashString(s2);

            v.emplace_back(s1, s2, h1, h2);
        }
    cout << "Size: " << v.size() << endl;

    double min = 100, max = 0, avg = 0, diff;
    pair<string, string> minP, maxP;
    for (auto el : v)
    {
        diff = CalculateSimilarity(el.h1, el.h2);
        if (diff > max)
        {
            max = diff;
            maxP.first = el.s1;
            maxP.second = el.s2;
        }
        if (diff < min)
        {
            min = diff;
            minP.first = el.s1;
            minP.second = el.s2;
        }
        avg += diff;
    }
    cout << "Max: " << max << " " << maxP.first << " " << maxP.second << endl;
    cout << "Min: " << min << " " << minP.first << " " << minP.second << endl;
    cout << "Avg: " << avg / v.size() << endl;
}
// e5c9aa2c1b
// a6fcf8bf35
// 86c80b9e08
// 2b490c5961
// cfa115966a
// a02206d4c7
// 8ba2

// e5c9aa2c1b
// a6fcf8bf35
// 86c80b9e08
// 2b490c5961
// cfa115966a
// a02206d4c7
// 8ba
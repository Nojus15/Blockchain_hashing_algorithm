#include "Hasher.h"

string Hasher::hashString(string stringToHash, bool coutTime)
{
    if (stringToHash.empty())
        throw std::invalid_argument("No text provided");

    timer.Start();
    this->text = stringToHash;
    this->calcSeed();
    this->convertToBinary();
    this->makeMultipleOf512();
    this->modifyAddedZeros();
    this->convertBinaryToHex();
    this->timeTaken = timer.Stop();
    if (coutTime)
        cout << "Time taken to hash string: " << timeTaken << " s" << endl;

    return this->hash;
}
double Hasher::getTimeTaken()
{
    return this->timeTaken;
}

void Hasher::convertToBinary()
{
    for (auto &l : text)
    {
        this->binaryText << std::bitset<8>(l).to_string();
    }
}

void Hasher::makeMultipleOf512()
{
    int bitSystem = 512;
    this->addedBits = bitSystem - this->text.length() * 8 % bitSystem;
    if (this->addedBits > 0)
        this->binaryText << '1' << std::string(this->addedBits - 1, '0');
}
string Hasher::rotateLeft(int posCount, string block)
{
    size_t length = block.length();
    return block.substr(posCount, length - posCount) + block.substr(0, posCount);
}
string Hasher::rotateRight(int posCount, string block)
{
    size_t length = block.length();
    return block.substr(length - posCount, posCount) + block.substr(0, length - posCount);
}
string Hasher::shiftRight(int posCount, string block)
{
    size_t length = block.length();
    return std::string(posCount, '0') + block.substr(0, length - posCount);
};
string Hasher::shiftLeft(int posCount, string block)
{
    size_t length = block.length();
    return block.substr(posCount, length - posCount) + std::string(posCount, '0');
};
void Hasher::calcSeed()
{
    this->seed = (int)this->text[0];

    for (auto &l : text)
    {
        seed += ((int)l * (seed % 3 + 1));
    }
}
void Hasher::modifyAddedZeros()
{
    this->binaryTextStr = this->binaryText.str();
    this->binaryText.str("");

    for (size_t i = 0; i < this->binaryTextStr.length() - 1; i += (this->seed % 13 + 7))
        this->binaryTextStr[i] == '1' ? this->binaryTextStr[i] = '0' : this->binaryTextStr[i] = '1';

    std::bitset<32> t1;
    std::bitset<32> t2;
    string s1;
    string s2;

    for (size_t i = 0; i < binaryTextStr.length(); i += 32)
    {
        t1 = ((bitset<32>)this->rotateRight(7, binaryTextStr.substr(i, 32)) ^ (bitset<32>)this->rotateRight(18, binaryTextStr.substr(i, 32)) ^ (bitset<32>)this->shiftRight(3, binaryTextStr.substr(i, 32)));
        t2 = ((bitset<32>)this->rotateRight(17, binaryTextStr.substr(i, 32)) ^ (bitset<32>)this->rotateRight(19, binaryTextStr.substr(i, 32)) ^ (bitset<32>)this->shiftRight(10, binaryTextStr.substr(i, 32)));
        t1.flip(2).flip(5).flip(11).flip(17).flip(23).flip(31);
        t2.flip(3).flip(7).flip(13).flip(19).flip(29).flip(1);
        s1 = this->addBinary(binaryTextStr.substr(i, 32), t1.to_string());
        s2 = this->addBinary(binaryTextStr.substr(i / 2, 32), t2.to_string());
        this->binaryTextStr.replace(i, 32, this->addBinary(s1, s2));
    }
};
string Hasher::addBinary(string b1, string b2)
{
    int length = b1.length();

    int sum[length] = {0};
    int carry = 0;
    for (int i = length - 1; i > -1; i--)
    {
        int t = (int)b1[i] + (int)b2[i] - '0' * 2;
        sum[i] = (t + carry) % 2;
        carry = (t + carry) / 2;
    }

    stringstream ss;
    for (int i : sum)
        ss << i;
    return ss.str();
};

void Hasher::convertBinaryToHex()
{
    string tmp;
    stringstream res;
    string t;
    int pos = this->seed % (this->binaryTextStr.length() - 64 * 4);
    // cout << "Pos: " << pos << " Seed:" << seed << endl;
    // cout << "Lenght: " << this->binaryTextStr.length() << endl;

    for (int i = 0; i < 4; i++)
    {
        t = this->binaryTextStr.substr(pos + 64 * i, 64);
        if (t.substr(0, 4) == "0000")
            t[0] = '1';
        bitset<64> hashSet(t);
        // cout << "hashSet size: " << hashSet.size() << " " << this->binaryTextStr.substr(pos + 64 * i, 64) << " " << hex << hashSet.to_ullong() << endl;
        res << hex << hashSet.to_ullong();
    }
    this->hash = res.str();
}
// e4d5160dd3
// 7e7c5f9ac3
// 6405cf0415
// a4862cb0e7
// d08acb3550
// 11036a63c5
// d16f
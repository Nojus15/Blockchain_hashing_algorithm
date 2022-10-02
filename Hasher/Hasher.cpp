#include "Hasher.h"

string Hasher::hashString(string stringToHash)
{
    if (stringToHash.empty())
        throw std::invalid_argument("No text provided");

    this->text = stringToHash;
    this->convertToBinary();
    this->makeMultipleOf512();
    this->modifyAddedZeros();
    this->convertBinaryToHex();

    return this->hash;
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

void Hasher::modifyAddedZeros()
{
    this->binaryTextStr = this->binaryText.str();
    this->binaryText.str("");

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
    size_t seed = 0;

    for (auto &l : text)
        seed += l;

    int pos = seed % (this->binaryTextStr.length() - 64 * 4);

    for (int i = 0; i < 4; i++)
    {
        bitset<64> hashSet(this->binaryTextStr.substr(pos + 64 * i, 64));
        res << hex << hashSet.to_ullong();
    }
    this->hash = res.str();
}
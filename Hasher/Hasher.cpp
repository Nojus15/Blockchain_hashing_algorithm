#include "Hasher.h"

string Hasher::hashString(string stringToHash)
{
    if (stringToHash.empty())
        throw std::invalid_argument("No text provided");

    this->text = stringToHash;
    this->convertToBinary();
    this->makeMultipleOf512();

    string binaryTextStr = this->binaryText.str();
    this->binaryText.clear();
    for (size_t i = 0; i < binaryTextStr.length() / 512; i++)
    {
        cout << "loop " << i << endl;
        binaryText << ((bitset<64>)this->rotateLeft(7, binaryTextStr.substr((i + 0) * 64, (i + 1) * 64 - 1)) ^ (bitset<64>)this->rotateRight(15, binaryTextStr.substr((i + 0) * 64, (i + 1) * 64 - 1)));
        binaryText << ((bitset<64>)this->rotateLeft(9, binaryTextStr.substr((i + 1) * 64, (i + 2) * 64 - 1)) ^ (bitset<64>)this->rotateRight(13, binaryTextStr.substr((i + 1) * 64, (i + 2) * 64 - 1)));
        binaryText << ((bitset<64>)this->rotateLeft(5, binaryTextStr.substr((i + 2) * 64, (i + 3) * 64 - 1)) ^ (bitset<64>)this->rotateRight(17, binaryTextStr.substr((i + 2) * 64, (i + 3) * 64 - 1)));
        binaryText << ((bitset<64>)this->rotateLeft(11, binaryTextStr.substr((i + 3) * 64, (i + 4) * 64 - 1)) ^ (bitset<64>)this->rotateRight(7, binaryTextStr.substr((i + 3) * 64, (i + 4) * 64 - 1)));
        binaryText << ((bitset<64>)this->rotateLeft(17, binaryTextStr.substr((i + 4) * 64, (i + 5) * 64 - 1)) ^ (bitset<64>)this->rotateRight(2, binaryTextStr.substr((i + 4) * 64, (i + 5) * 64 - 1)));
        binaryText << ((bitset<64>)this->rotateLeft(9, binaryTextStr.substr((i + 5) * 64, (i + 6) * 64 - 1)) ^ (bitset<64>)this->rotateRight(8, binaryTextStr.substr((i + 5) * 64, (i + 6) * 64 - 1)));
        binaryText << ((bitset<64>)this->rotateLeft(3, binaryTextStr.substr((i + 6) * 64, (i + 7) * 64 - 1)) ^ (bitset<64>)this->rotateRight(6, binaryTextStr.substr((i + 6) * 64, (i + 7) * 64 - 1)));
        binaryText << ((bitset<64>)this->rotateLeft(1, binaryTextStr.substr((i + 7) * 64, (i + 8) * 64 - 1)) ^ (bitset<64>)this->rotateRight(4, binaryTextStr.substr((i + 7) * 64, (i + 8) * 64 - 1)));
    }
    // cout << ((bitset<4>)"1011" ^ (bitset<4>)"1101") << endl;
    // cout << this->rotateLeft(3, "00011111111") << endl;
    // cout << this->rotateRight(3, "00011111111") << endl;
    cout << binaryTextStr.length() << "Og text: " << endl;
    cout << "test" << binaryTextStr[binaryTextStr.length()] << "test" << endl;
    cout << binaryTextStr << endl;
    cout << endl;
    return this->binaryText.str();
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
    int bitsToAdd = bitSystem - this->text.length() * 8 % bitSystem;
    cout << "bitsToAdd: " << bitsToAdd << endl;
    this->binaryText << '1' << std::string(bitsToAdd - 1, '0');
}
string Hasher::rotateLeft(int posCount, string block)
{
    size_t length = block.length();
    return block.substr(posCount, length) + block.substr(0, posCount);
}
string Hasher::rotateRight(int posCount, string block)
{
    size_t length = block.length();
    return block.substr(length - posCount, length) + block.substr(0, length - posCount);
}
void Hasher::modifyAddedZeros()
{
}
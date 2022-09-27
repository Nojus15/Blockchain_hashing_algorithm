#include "Hasher.h"

string Hasher::hashString(string stringToHash)
{
    if (stringToHash.empty())
        throw std::invalid_argument("No text provided");

    this->text = stringToHash;
    this->convertToBinary();
    this->makeMultipleOf512();
    this->modifyAddedZeros();
    cout << "Og: " << binaryTextStr << endl;
    cout << this->convertBinaryToHex() << endl;
    // cout << "Hashed: " << this->binaryText.str() << endl;

    return binaryTextStr;
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
    //     s0 = (w[i-15] rightrotate 7) xor (w[i-15] rightrotate 18) xor (w[i-15] rightshift 3)
    //     s1 = (w[i- 2] rightrotate 17) xor (w[i- 2] rightrotate 19) xor (w[i- 2] rightshift 10)
    //     w[i] = w[i-16] + s0 + w[i-7] + s1
    this->binaryTextStr = this->binaryText.str();
    this->binaryText.str("");

    size_t binaryLenght = binaryTextStr.length();
    size_t posToStart = binaryLenght - this->addedBits;

    std::bitset<32> t1;
    std::bitset<32> t2;
    string s1;
    string s2;

    for (size_t i = posToStart; i < binaryLenght - 1; i += 32)
    {
        t1 = ((bitset<32>)this->rotateRight(7, binaryTextStr.substr(i - posToStart, 32)) ^ (bitset<32>)this->rotateRight(18, binaryTextStr.substr(i - posToStart, 32)) ^ (bitset<32>)this->shiftRight(3, binaryTextStr.substr(i - posToStart, 32)));
        t2 = ((bitset<32>)this->rotateRight(17, binaryTextStr.substr(i - posToStart, 32)) ^ (bitset<32>)this->rotateRight(19, binaryTextStr.substr(i - posToStart, 32)) ^ (bitset<32>)this->shiftRight(10, binaryTextStr.substr(i - posToStart, 32)));
        t1.flip(2).flip(5).flip(11).flip(17).flip(23).flip(31);
        t2.flip(3).flip(7).flip(13).flip(19).flip(29).flip(1);
        s1 = this->addBinary(binaryTextStr.substr(i - posToStart, 32), t1.to_string());
        s2 = this->addBinary(binaryTextStr.substr(i - posToStart / 2, 32), t2.to_string());
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

string Hasher::convertBinaryToHex()
{
    string res, tmp;
    size_t len = this->binaryTextStr.length() / 4;
    for (int i = this->binaryTextStr.length(); i > this->binaryTextStr.length() - 64 * 4; i -= 4)
    {
        tmp = this->binaryTextStr.substr(i, 4);
        if (!tmp.compare("0000"))
        {
            res = res + "0";
        }
        else if (!tmp.compare("0001"))
        {
            res = res + "1";
        }
        else if (!tmp.compare("0010"))
        {
            res = res + "2";
        }
        else if (!tmp.compare("0011"))
        {
            res = res + "3";
        }
        else if (!tmp.compare("0100"))
        {
            res = res + "4";
        }
        else if (!tmp.compare("0101"))
        {
            res = res + "5";
        }
        else if (!tmp.compare("0110"))
        {
            res = res + "6";
        }
        else if (!tmp.compare("0111"))
        {
            res = res + "7";
        }
        else if (!tmp.compare("1000"))
        {
            res = res + "8";
        }
        else if (!tmp.compare("1001"))
        {
            res = res + "9";
        }
        else if (!tmp.compare("1010"))
        {
            res = res + "a";
        }
        else if (!tmp.compare("1011"))
        {
            res = res + "b";
        }
        else if (!tmp.compare("1100"))
        {
            res = res + "c";
        }
        else if (!tmp.compare("1101"))
        {
            res = res + "d";
        }
        else if (!tmp.compare("1110"))
        {
            res = res + "e";
        }
        else if (!tmp.compare("1111"))
        {
            res = res + "f";
        }
        else
        {
            continue;
        }
    }
    return res;
}

// 61616161617373737373737373730810504EE2E6B79A8FE321B42BCE29825EBD5E310E48E6E3022F7C05BFB8982F0D9010FD048148A284E1913272259E875680EAB9
// 61616161617373737373737373CBD41412A6AA814FC0D3FD3C801107627D6051DB9B62C22759F2F1B3A178E66E2E3B59BA1709FB7C81AB43551A91D565F680ACD8
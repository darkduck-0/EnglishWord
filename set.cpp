#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "word.cpp"
#include "sign.h"

using std::cout, std::cin;
using std::string, std::vector;

std::vector<Word> wordTable;
string fileName;
int16_t level;

int load()
{
    std::ifstream file(fileName);
    if (!file.is_open())
    {
        std::cout << "can not open file: " << fileName << " .\n";
        return FERR;
    }
    std::string eng, chi;
    uint64_t cTime, nTime;
    int16_t tlevel;
    while (file >> eng >> chi)
    {
        file.ignore();
        file.read(reinterpret_cast<char *>(&cTime), sizeof(cTime));
        file.read(reinterpret_cast<char *>(&tlevel), sizeof(tlevel));
        file.read(reinterpret_cast<char *>(&nTime), sizeof(nTime));
        file.ignore();
        wordTable.emplace_back(eng, chi, cTime, level, nTime);
    }
    return FINI;
}

int save()
{
    std::ofstream file(fileName);
    if (!file.is_open())
    {
        std::cout << "can not open file: " << fileName << std::endl;
        return FERR;
    }
    for (auto &i : wordTable)
    {
        file << i;
    }
    return FINI;
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        cout << "usage: file level\n";
        return UERR;
    }
    fileName = argv[1];
    level = std::stoi((string)(argv[2]));
    if (level < 0 || level > 12)
    {
        cout << "invalid level.\n";
        return UERR;
    }
    int sign;
    if ((sign = load()) != FINI)
        return sign;
    for (auto i : wordTable)
        cout << i;
    if ((sign = save()) != FINI)
        return sign;
    return FINI;
}
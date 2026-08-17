#include "word.h"
#include "sign.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using std::cout, std::cin,
    std::string, std::vector,
    std::ifstream, std::ofstream,
    std::endl;

sign loadFile(string fileName, vector<Word> &wordTable)
{
    if (fileName == "/back")
    return QUIT;
    ifstream file(fileName);
    if (!file.is_open())
    {
        cout << "Can not open file: " << fileName << '\n';
        return FERR;
    }
    string eng, chi;
    uint64_t cTime, nTime;
    int16_t level;
    while (file >> eng >> chi)
    {
        file.ignore();
        file.read(reinterpret_cast<char *>(&cTime), sizeof(cTime));
        file.read(reinterpret_cast<char *>(&level), sizeof(level));
        file.read(reinterpret_cast<char *>(&nTime), sizeof(nTime));
        wordTable.emplace_back(eng, chi, cTime, level, nTime);
    }
    return FINI;
}

sign saveFile(string fileName, vector<Word> &wordTable)
{
    ofstream file(fileName);
    if (!file.is_open())
    {
        cout << "can not open file: " << fileName << endl;
        return FERR;
    }
    for (auto &i : wordTable)
        file << i;
    return FINI;
}

int importWord(std::istream &source, vector<Word> &wordTable)
{
    wordTable.clear();
    string eng, chi;
    while(source >> eng)
    {
        if (eng == "/back")
            break;
        source >> chi;
        wordTable.emplace_back(eng, chi, 0, 0, 0);
    }
    return wordTable.size();
}

int main()
{
    ifstream file("words/a.txt");
    vector<Word> v;
    cout << importWord(file, v) << endl;
    for (auto &i : v)
        cout << i << endl;
    cout << importWord(cin, v) << endl;
    for (auto &i : v)
        cout << i << endl;
 
}
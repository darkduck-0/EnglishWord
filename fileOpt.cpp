#include "fileOpt.h"
#define NOBUG

using std::cout, std::cin,
    std::string, std::vector,
    std::ifstream, std::ofstream,
    std::endl;

int loadFile(ifstream &file, vector<Word> &wordTable)
{
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
    return wordTable.size();
}

int saveFile(ofstream &file, vector<Word> &wordTable)
{
    for (auto &i : wordTable)
        file << i;
    return wordTable.size();
}

int importWord(std::istream &source, vector<Word> &wordTable)
{
    wordTable.clear();
    string eng, chi;
    while (source >> eng)
    {
        if (eng == "/back")
            break;
        source >> chi;
        wordTable.emplace_back(eng, chi, 0, 0, 0);
    }
    return wordTable.size();
}

#ifndef NOBUG
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
#endif
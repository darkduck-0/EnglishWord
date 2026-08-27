#include "fileOrg.h"
#include <cstring>

// #define NOBUG

using std::ifstream, std::ofstream;
using std::stringstream, std::vector, std::string;

static int parseWord(string &source, vector<Word> &dest, size_t index)
{
    static string eng, chi;
    static uint64_t lastTime, nextTime;
    static int16_t level;
    int count = 0;

    for (; index < source.size();)
    {
        eng.clear();
        for (char c;(c = source[index++]) != '\t'; eng.push_back(c));

        chi.clear();
        for (char c;(c = source[index++]) != '\t'; chi.push_back(c));

        memcpy(&lastTime, &source[index], sizeof(lastTime));
        index += sizeof(lastTime);
        memcpy(&level, &source[index], sizeof(level));
        index += sizeof(level);
        memcpy(&nextTime, &source[index], sizeof(nextTime));
        index += sizeof(nextTime);

        dest.emplace_back(eng, chi, lastTime, level, nextTime);
        ++index;
        ++count;
    }

    return count;
}

int loadFile(string &fileName, vector<Word> &words)
{
    static ifstream inFile;

    inFile.open(fileName, std::ios::binary | std::ios::ate);
    if (!inFile.is_open())
    {
        inFile.close();
        return -1;
    }

    size_t fileSize = inFile.tellg();
    string buffer(fileSize, '\0');

    inFile.seekg(0, std::ios::beg);
    inFile.read(&buffer.front(), fileSize);
    inFile.close();

    return parseWord(buffer, words, 0);
}

int saveFile(string &fileName, vector<Word> &words)
{
    static ofstream outFile;
    int count = 0;

    outFile.open(fileName, std::ios::binary);
    if (!outFile.is_open())
    {
        outFile.close();
        return -1;
    }

    for (auto &i : words)
    {
        outFile << i;
        ++count;
    }

    return count;
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
    vector<Word> v;
    string name = "a";
    loadFile(name, v);
    for (auto &i : v)
        std::cout << i;
    std::cout << std::flush;
    std::cout << v.size() << std::endl;
}
#endif
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "word.cpp"

enum sign
{
    UERR,
    FERR,
    QUIT,
    FINI,
    REBOOT
};

std::vector<Word> wordTable;

int load()
{
    std::cout << "The file name: ";
    std::string name;
    std::cin >> name;
    std::ifstream file(name);
    if (name == "/back")
        return -1;
    if (!file.is_open())
    {
        std::cout << "can not open file: " << name << " .\n";
        return 1;
    }
    std::string eng, chi;
    uint64_t cTime, nTime;
    uint16_t level;
    int count = 0;
    while (file >> eng >> chi)
    {
        ++count;
        file.ignore();
        file.read(reinterpret_cast<char *>(&cTime), sizeof(cTime));
        file.read(reinterpret_cast<char *>(&level), sizeof(level));
        file.read(reinterpret_cast<char *>(&nTime), sizeof(nTime));
        file.ignore();
        wordTable.emplace_back(eng, chi, cTime, level, nTime);
    }
    return count;
}

int main()
{
    load();
    int last = 0;
    while (true)
    {
        for (int count = 0; count < 10 && last + count < wordTable.size(); ++count)
        {
            std::cout << last + count << '\t';
            std::cout << wordTable[last + count];
        }
        std::string cmd;
        std::cin >> cmd;
        if (cmd == "up")
        {
            last -= 10;
            last = last < 0 ? 0 : last;
            continue;
        }
        if (cmd == "down")
        {
            last += 10;
            int t = wordTable.size() - 10;
            last = last < t ? last : t;
            last = last < 0 ? 0 : last;
            continue;
        }
        if (cmd == "back")
        {
            return 0;
        }
        uint c;
        std::cin >> c;
        // check c
        while (true)
        {
            std::cout << wordTable[c];
            std::cin >> cmd;
            if (cmd == "back")
            {
                break;
            }
            if (cmd == "eng")
            {
                std::cin >> wordTable[c].eng;
                continue;
            }
            if (cmd == "chi")
            {
                std::cin >> wordTable[c].chi;
                continue;
            }
            if (cmd == "last")
            {
                std::cin >> wordTable[c].currentTime;
                continue;
            }
            if (cmd == "level")
            {
                std::cin >> wordTable[c].level;
                continue;
            }
            if (cmd == "next")
            {
                std::cin >> wordTable[c].nextTime;
                continue;
            }
        }
    }
    return 0;
}
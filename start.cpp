#include <fstream>
#include <iostream>
#include <vector>
#include "word.cpp"
#include <algorithm>
#include <random>
#include <ctime>

std::random_device rd;
std::vector<Word> wordTable;
std::vector<Word *> New, Old;
uint right;

class Settings
{
public:
    uint32_t men;
    uint32_t cdw;

} setting = {2, 4};

auto compare = [](Word *x, Word *y)
{ return *x > *y; };

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
        wordTable.emplace_back(eng, chi, cTime, level, nTime);
    }
    return count;
}

int init()
{
    if (load() < setting.cdw)
    {
        std::cout << "To few words.\n";
        return -1;
    }
    if (wordTable.empty())
    {
        std::cout << "The file is empty.\n";
        return -1;
    }
    for (auto &i : wordTable)
    {
        if (i.currentTime == 0)
            New.push_back(&i);
        else
            Old.push_back(&i);
    }
    if (Old.empty())
    {
        Old.push_back(New.back());
        New.pop_back();
    }
    std::make_heap(Old.begin(), Old.end(), compare);
    return 0;
}

int randit()
{
    static std::vector<std::string *> qus;
    right = rd() % (setting.cdw);
    qus.clear();
    qus.emplace_back(&Old.front()->chi);
    for (uint i = 1; i < setting.cdw && i < wordTable.size(); ++i)
    {
        qus.emplace_back(&(wordTable[i].chi));
    }
    std::string *t = qus[right];
    qus[right] = qus[0];
    qus[0] = t;
    std::cout << Old.front()->eng << std::endl;
    for (auto &i : qus)
    {
        std::cout << *i << std::endl;
    }
    return 0;
}

int choise(uint real, uint chs, bool init)
{
    static uint count;
    if (init)
        count = 0;
    Word &w = wordTable.front();
    if (real == chs)
    {
        ++Old.front()->level;
        return 0;
    }
    ++count;
    --w.level;
    if (count <= setting.men && w.level >= 0)
    {
        return 1;
    }
    w.level = w.level < 0 ? 0 : w.level;
    return -1;
}

int collate()
{
    Old[0]->updateTime();
    std::pop_heap(Old.begin(), Old.end());
    std::push_heap(Old.begin(), Old.end(), compare);
    uint64_t now = time(0);
    if (now < Old[0]->nextTime)
    {
        if (New.empty())
        {
            std::cout << "No task now.\n";
            return -1;
        }
        Old.push_back(New.back());
        New.pop_back();
    }
    return 0;
}

// debug
void display(const std::string name, std::vector<Word> &v)
{
    std::cout << '\t' << name << std::endl;
    for (auto &i : v)
        std::cout << i;
    std::cout << std::endl;
}
void display(const std::string name, std::vector<Word *> &v)
{
    std::cout << '\t' << name << std::endl;
    for (auto &i : v)
        std::cout << *i;
    std::cout << std::endl;
}
// debug

int main()
{
    if (init() == -1)
        return 0;

    // debug
    display("wordTable:", wordTable);
    // debug

    while (true)
    {
        // debug
        display("Old:", Old);
        display("New:", New);
        // debug

        randit();
        std::cout << "right ans: " << right << std::endl;
        uint chs;
        std::cin >> chs;
        if (choise(right, chs, 1) == 1)
        {
        chos:
            std::cin >> chs;
            if (choise(right, chs, 0) == 1)
                goto chos;
        }
        if (collate() == -1)
        {
            return 0;
        }
    }
    return 0;
}
// load 返回 读到多少个word
// choise 简化操作，删除静态变量，删除初始化标签。
#include "start.h"

std::random_device rd;
std::vector<Word> wordTable;
std::vector<Word *> New, Old;
std::string fileName;
uint32_t right;
uint32_t errCount;

Settings setting = {1, 4};

auto compare = [](Word *x, Word *y)
{ return *x > *y; };

int load()
{
    std::ifstream file(fileName);
    if (fileName == "/back")
        return QUIT;
    if (!file.is_open())
    {
        std::cout << "can not open file: " << fileName << " .\n";
        return REBOOT;
    }
    std::string eng, chi;
    uint64_t cTime, nTime;
    uint16_t level;
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

int init()
{
    if (wordTable.size() < setting.cdw) // this will be deleted.
    {
        std::cout << "To few words.\n";
        return UERR;
    }
    // delete to here.
    if (wordTable.empty())
    {
        std::cout << "The file is empty.\n";
        return UERR;
    }
    for (auto &i : wordTable)
    {
        if (i.currentTime == 0)
            New.push_back(&i);
        else
            Old.push_back(&i);
    }
    while (Old.size() < setting.cdw)
    {
        Old.push_back(New.back());
        New.pop_back();
        Old.front()->initTime();
    }
    std::make_heap(Old.begin(), Old.end(), compare);
    return FINI;
}

int know()
{
    std::cout << Old.front()->eng << std::endl;
    while (true)
    {
        std::cout << "1.I know.\n";
        std::cout << "2.I do not know.\n";
        std::string cmd;
        std::cin >> cmd;
        if (cmd == "1")
        {
            return FINI;
        }
        else if (cmd == "2")
        {
            return UERR;
        }
        else if (cmd == "/back")
        {
            return QUIT;
        }
    }
}

int ranopt()
{
    static std::vector<std::string *> qus;
    right = rd() % (setting.cdw);
    qus.clear();
    // bug: 重复的正确选项
    // 暂时不修改，等加入大辞典后，从词典抽词。使用字典检测碰撞。
    // 后续加入形近字选项。
    for (int i = 0; i < setting.cdw && i < Old.size(); ++i)
    {
        qus.emplace_back(&(Old[i]->chi));
    }
    std::string *t = qus[right];
    qus[right] = qus[0];
    qus[0] = t;
    std::cout << '\t' << Old.front()->eng << std::endl;
    for (int i = 0; i < qus.size(); ++i)
    {
        std::cout << i + 1 << '\t';
        std::cout << *qus[i] << std::endl;
    }
    ++right;
    return FINI;
}

int samilar()
{
    return 0;
}

int choise()
{
    uint32_t cho;
    std::cin >> cho;
    if (std::cin.fail())
    {
        std::string cmd;
        std::cin.clear();
        std::cin >> cmd;
        if (cmd == "/back")
        {
            return QUIT;
        }
    }
    if (right == cho)
    {
        std::cout << "corract!\n";
        Old.front()->upGrade();
        return FINI;
    }
    ++errCount;
    if (Old.front()->deGrade() || errCount >= setting.men)
    {
        std::cout << "wrong!\n";
        // pause();
        return UERR;
    }
    else
    {
        return REBOOT;
    }
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
    return 0;
}

int collate()
{
    Old.front()->updateTime();
    std::pop_heap(Old.begin(), Old.end(), compare);
    std::push_heap(Old.begin(), Old.end(), compare);
    uint64_t now = time(0);
    if (now < Old.front()->nextTime)
    {
        if (New.empty())
        {
            std::cout << "No task now.\n";
            save(); // do i need this line?
            return QUIT;
        }
        Old.push_back(New.back());
        New.pop_back();
        Old.back()->initTime(); // what will happen while i delete this line?
        std::push_heap(Old.begin(), Old.end(), compare);
    }
    return FINI;
}

// debug
void display(const std::string name, std::vector<Word> &v)
{
    std::cout << '\t' << name << std::endl;
    if (v.empty())
    {
        std::cout << "empty!\n";
        return;
    }
    for (auto &i : v)
        std::cout << i;
    std::cout << std::endl;
}
void display(const std::string name, std::vector<Word *> &v)
{
    std::cout << '\t' << name << std::endl;
    if (v.empty())
    {
        std::cout << "empty!\n";
        return;
    }
    for (auto &i : v)
        std::cout << *i;
    std::cout << std::endl;
}
// debug

int shell()
{
reload:
    switch (load())
    {
    case QUIT:
        // clear
        return FINI;
    case REBOOT:
        // clear
        goto reload;
    case FINI:
        // clear
    default:
        break;
    }

    switch (init())
    {
    case UERR:
        // pause
        // clear
        goto reload;
    case FINI:
    default:
        break;
    }

    while (true)
    {
        ranopt();
        errCount = 0;
    rechoose:
        switch (choise())
        {
        case FINI:
        case UERR:
            std::cout << Old.front()->eng << '\t' << Old.front()->chi << std::endl;
            std::cout << "level: " << Old.front()->level << std::endl;
            std::cin.get();
            // clear
            break;
        case REBOOT:
            // clear
            goto rechoose;
        case QUIT:
            save();
            goto reload;
        default:
            break;
        }
        if (collate() == QUIT)
        {
            save();
            goto reload;
        }
    }
    return FINI;
}

#ifndef nobug
int main(int argc, char *argv[])
{
    if (argv[1] == nullptr)
    {
        std::cout << "example: start fileName\n";
        return UERR;
    }
    fileName = argv[1];
    shell();
    return FINI;
}
#endif

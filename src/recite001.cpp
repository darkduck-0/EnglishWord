#include "winbuild.h"
#include "recite.h"

#define REDOPEN "\033[31m"
#define GREOPEN "\033[32m"
#define RESET "\033[0m"

using std::cout, std::cin, std::endl;
using std::ifstream, std::ofstream;
using std::string, std::vector;

uint32_t errMax = 0;
uint32_t qusNum = 4;
string misRem = REDOPEN "Honestly, I misremembered.\n" RESET;
string noRit = GREOPEN "No correct option.\n" RESET;
uint32_t errWord;


sign init()
{
    cout << "\033[?251";
    // hide I

#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    words.reserve(1024);
    Old.reserve(1024);
    New.reserve(1024);
    chis.reserve(1024);
    qus.resize(qusNum + 1);
    qus[qusNum - 1] = &noRit;
    qus[qusNum] = &misRem;

    if (words.empty())
    {
        cout << REDOPEN "The file is empty.\n" RESET;
        return UERR;
    }

    if (words.size() < qusNum)
    {
        cout << REDOPEN "Too few words.\n" RESET;
        return UERR;
    }

    for (auto &i : words)
    {
        chis.push_back(&(i.chi));
        if (i.lastTime)
            Old.push_back(&i);
        else
            New.push_back(&i);
    }
    std::reverse(New.begin(), New.end());

    while (Old.size() < qusNum)
    {
        Old.push_back(New.back());
        New.pop_back();
        Old.front()->initTime();
    }
    std::make_heap(Old.begin(), Old.end(), compare);

    if (time(0) < Old.front()->nextTime)
    {
        cout << REDOPEN "No task now.\n" RESET;
        return QUIT;
    }

    return FINI;
}

sign ranOpt()
{
    static int index = 0;
    if (index + qusNum >= words.size())
    {
        index = 0;
        std::shuffle(chis.begin(), chis.end(), gen);
    }

    uint32_t rand = rd();
    bool noRight;
    noRight = rand & 0x01;
    ritChs = rd() % (qusNum - 1);

    int i = 0;
    if (!noRight)
        qus[i++] = &(Old.front()->chi);
    else
        ritChs = qusNum;

    for (; i < qusNum - 1; ++index)
    {
        if (&(Old.front()->chi) == chis[index])
            continue;
        qus[i++] = chis[index];
    }

    string *t = qus[ritChs];
    qus[ritChs] = qus[0];
    qus[0] = t;
    ++ritChs;
    return FINI;
}

sign judge()
{
    uint32_t chos;
    if (scanf("%d", &chos) != 1)
    {
        string cmd;
        cin >> cmd;
        if (cmd == "/back")
        {
            return QUIT;
        }
        return REBOOT;
    }

    if (chos < 1 || chos > qusNum)
        return REBOOT;

    if (chos == ritChs)
    {
        Old.front()->upGrade();
        cout << GREOPEN "corract." RESET << " level: " << Old.front()->level << endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        return FINI;
    }

    ++errWord;
    ++errCount;
    cout << "\033[31mwrong.\033[0m\n";

    if (Old.front()->deGrade() || errCount > errMax)
    {
        return UERR;
    }

    return REBOOT;
}

sign collate()
{
    Old.front()->updateTime();
    std::pop_heap(Old.begin(), Old.end(), compare);
    std::push_heap(Old.begin(), Old.end(), compare);
    uint64_t now = time(0);
    if (now < Old.front()->nextTime)
    {
        if (New.empty())
        {
            cout << REDOPEN "No task now.\n" RESET;
            return QUIT;
        }
        Old.push_back(New.back());
        New.pop_back();
        Old.back()->initTime();
        std::push_heap(Old.begin(), Old.end(), compare);
    }
    return FINI;
}

void opt()
{
    cout << Old.front()->eng << endl;
    for (int i = 0; i <= qusNum; ++i)
    {
        cout << i + 1 << ". " << *qus[i] << endl;
    }
}

sign know()
{
    cout << Old.front()->eng << endl;
    cout << "1. " GREOPEN "I know.\n" RESET;
    cout << "2. " REDOPEN "I do not know.\n" RESET;
    while (true)
    {
        string cmd;
        cin >> cmd;
        if (cmd == "1")
            return FINI;
        else if (cmd == "2")
            return UERR;
        else if (cmd == "/back")
            return QUIT;
    }
}

sign save()
{
    cout << "\033[?25h";
    string tempFile = fileName + ".tmp";
    ofstream file(tempFile);
    if (!file.is_open())
    {
        cout << "\033[31mcan not creat file: " << tempFile << ".\033[0m\n";
        return FERR;
    }
    saveFile(file, words);
    file.close();
    remove(fileName.c_str());
    rename(tempFile.c_str(), fileName.c_str());

    return FINI;
}
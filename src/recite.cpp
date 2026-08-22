#include "recite.h"

using std::cout, std::cin, std::endl;
using std::ifstream, std::ofstream;
using std::string, std::vector;

uint32_t errMax = 0;
uint32_t qusNum = 4;

int main(int argc, char *argv[])
{
    fileName = argv[1];
    ifstream inFile(fileName);
    if (!inFile.is_open())
    {
        cout << "\033[31mcan not open file: " << fileName << ".\033[0m\n";
        return FERR;
    }
    loadFile(inFile, words);
    if (init() != FINI)
        return UERR;
    while (true)
    {
        cout << "\033[2J\033[H\033[3J";
        ranOpt();
        errCount = 0;
        switch (know())
        {
        case UERR:
            Old.front()->deGrade();
        wrong:
            cout << "\033[2J\033[H\033[3J";
            cout << Old.front()->eng << ": " << Old.front()->chi << endl;
            cout << "level: " << Old.front()->level << endl;
            cout << "\nI know.";
            getchar();
            getchar();
            goto wordDone;
        case QUIT:
            goto quit;
        case FINI:
        default:
            break;
        }
    rechoose:
        cout << "\033[2J\033[H\033[3J";
        opt();
        switch (judge())
        {
        case QUIT:
            goto quit;
        case REBOOT:
            goto rechoose;
        case UERR:
            Old.front()->deGrade();
            goto wrong;
        case FINI:
        default:
            break;
        }
    wordDone:
        if (collate() == QUIT)
            break;
    }
quit:
    return save();
    // recite wordfile [mod]
}

sign ranOpt()
{
    ritChs = rd() % qusNum;
    static int index = 0;
    if (1 + index + qusNum >= words.size())
    {
        index = 0;
        std::shuffle(chis.begin(), chis.end(), gen);
    }

    qus[0] = &(Old.front()->chi);
    for (int i = 1; i < qusNum; ++index)
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
    if (chos == ritChs)
    {
        Old.front()->upGrade();
        cout << "\033[32mcorract.\033[0m" << " level: " << Old.front()->level << endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        return FINI;
    }
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
            cout << "\033[32mNo task now.\033[0m\n";
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
    for (int i = 0; i < qusNum; ++i)
    {
        cout << i + 1 << ". " << *qus[i] << endl;
    }
}

sign init()
{
    cout << "\033[?25l";
    words.reserve(MAXWORD);
    Old.reserve(MAXWORD);
    New.reserve(MAXWORD);
    chis.reserve(MAXWORD);
    qus.resize(qusNum);
    if (words.empty())
    {
        cout << "\033[31mThe file is empty.\033[0m\n";
        return UERR;
    }
    if (words.size() < qusNum)
    {
        cout << "\033[31mToo few words.\033[0m\n";
        return UERR;
    }
    for (auto &i : words)
    {
        chis.push_back(&(i.chi));
        if (i.currentTime)
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
    return FINI;
}

sign know()
{
    cout << Old.front()->eng << endl;
    cout << "1. \033[32mI know.\033[0m\n";
    cout << "2. \033[31mI do not know.\033[0m\n";
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
    remove(fileName.c_str());
    rename(tempFile.c_str(), fileName.c_str());

    return FINI;
}
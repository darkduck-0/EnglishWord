#include "wordsOpt.h"
#include "word.h"
#include "easyConsole.h"
#include <vector>
#include <iostream>
#include <random>
#include <thread>
#include <algorithm>

std::mt19937 gen(std::random_device{}());
std::random_device rd;

using std::cout, std::cin, std::endl;
using std::string, std::vector;

static const string noRightOpt = GreenOpen "No correct option." Reset;
static const string misMemOpt = RedOpen "Honestly, I misremembered." Reset;
static vector<const string *> opts, errWordTemp, errWordTotal, chis;
static uint32_t errWordCount;
static int rightOpt;

extern size_t optSize;       // from start
extern vector<Word *> ready; // from wordsOrg

extern void showProcess();

void initOpt()
{
    chis.reserve(1024);
    errWordTotal.reserve(1024);
    errWordTemp.resize(10);
    opts.resize(optSize + 1);

    opts[optSize - 1] = &noRightOpt;
    opts[optSize] = &misMemOpt;

    extern vector<Word> words;
    for (auto &i : words)
        chis.push_back(&(i.chi));
}

void randomOpt()
{
    static int index = 0;
    if (index + optSize >= chis.size())
    {
        index = 0;
        std::shuffle(chis.begin(), chis.end(), gen);
    }

    const string *rightChi = &ready.front()->chi;
    size_t i = 0;

    uint32_t rand = rd();
    bool noright = rand & 0x01;
    rightOpt = rand % (optSize - 1);

    if (!noright)
        opts[i++] = rightChi;
    else
        rightOpt = optSize;

    for (; i < optSize - 1; ++index)
    {
        if (chis[index] == rightChi)
            continue;
        opts[i++] = chis[index];
    }

    if (!noright)
    {
    rightChi = opts[rightOpt];
    opts[rightOpt] = opts[0];
    opts[0] = rightChi;
    ++rightOpt;
    }
}

void showOpt()
{
    cout << Clear << ready.front()->eng << endl;
    for (size_t i = 0; i <= optSize; ++i)
        cout << '[' << i + 1 << "] " << *opts[i] << endl;
}

sign judge()
{
    string cmd;
    for (;;)
    {
        cin >> cmd;
        if (cmd.size() > 1)
        {
            cout << "\033[1A\033[2K\r";
            continue;
        }

        int userOpt = cmd.front();
        if (userOpt == rightOpt + '0')
            return FINI;
        else if (userOpt == 'q')
            return QUIT;
        else
        {
            cout << "\033[1A\033[2K\r";
            return UERR;
        }
    }
}

sign know()
{
    cout << Clear;
    showProcess();
    cout << ready.front()->eng << endl;
    cout << "[1] " GreenOpen "I know." Reset << endl;
    cout << "[2] " RedOpen "I do not know." Reset << endl;

    while (true)
    {
        string cmd;
        cin >> cmd;
        if (cmd == "1")
            return FINI;
        else if (cmd == "2")
            return UERR;
        else if (cmd == "q")
            return QUIT;
        cout << "\033[1A\033[2K\r";
    }
}

void correct()
{
    Word *targetWord = ready.front();
    targetWord->upGrade();
    targetWord->updateTime();
    cout << GreenOpen "Correct." Reset "\t";
    targetWord->coutLevel() << endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(750));
}

void wrong()
{
    Word *targetWord = ready.front();
    targetWord->deGrade();
    targetWord->updateTime();
    cout << Clear RedOpen "Wrong." Reset "\n";
    targetWord->coutLevel() << '\n';
    cout << targetWord->eng << ": " << targetWord->chi << '\n';
    cout << "I know." << endl;
    char c;
    cin >> c;
}
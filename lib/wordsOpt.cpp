#include "wordsOpt.h"
#include <string>
#include <vector>
#include "word.h"
#include <random>
#include <thread>
#include "sign.h"
#include <algorithm>

#define RedOpen "\033[31m"
#define GreenOpen "\033[32m"
#define Reset "\033[0m"
#define HideCursor "\033[?25l"
#define ShowCursor "\033[?25h"
#define Clear "\033[H\033[J"


std::mt19937 gen(std::random_device{}());
std::random_device rd;

using std::cout, std::cin, std::endl;
using std::string, std::vector;


static vector<string *> opts, errWordTemp, errWordTotal, chis;
static string noRightOpt = GreenOpen "No correct option.\n" Reset;
static string misMemOpt = RedOpen "Honestly, I misremembered.\n" Reset;
static size_t rightOpt;
static uint32_t errWordCount;

extern size_t optSize;


void initOpt()
{
    extern vector<Word> words;
    chis.reserve(1024);
    errWordTemp.resize(10);
    errWordTotal.reserve(1024);

    opts.resize(optSize + 1);
    opts[optSize - 1] = &noRightOpt;
    opts[optSize] = &misMemOpt;

    for (auto &i : words)
        chis.push_back(&(i.chi));
}

void randomOpt(string *rightChi)
{
    static int index = 0;
    if (index + optSize >= chis.size())
    {
        index = 0;
        std::shuffle(chis.begin(), chis.end(), gen);
    }

    uint32_t rand = rd();
    bool noright = rand & 0x01;
    rightOpt = rand % (optSize - 1);

    size_t i = 0;
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

    string *t = opts[rightOpt];
    opts[rightOpt] = opts[0];
    opts[0] = t;
    ++rightOpt;
}


void showOpt(string *eng)
{
    cout << Clear << *eng << endl;
    for (size_t i = 0; i <= optSize; ++i)
        cout << i + 1 << ". " << *opts[i] << endl;
}


sign judge(Word *targetWord)
{
    size_t userOpt;
    if (scanf("%d", &userOpt) != 1)
    {
        string cmd;
        cin >> cmd;
        if (cmd == "/back")
            return QUIT;
        return REBOOT;
    }

    if (userOpt < 1 || userOpt > optSize + 1)
        return REBOOT;
    
    if (userOpt == rightOpt)
    {
        targetWord->upGrade();
        cout << GreenOpen "corract." Reset;
        cout << " level: " << targetWord->level << endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(750));
        return FINI;
    }

    // ++errWordCount;

    cout << Clear;
    cout << RedOpen "wrong." Reset;
    cout << " level: " << targetWord->level << endl;

    cout << targetWord->eng << ": " << targetWord->chi << endl;
    cout << "I know.\n";

    return UERR;
}


sign know(Word *targetWord)
{
    cout << targetWord->eng << endl;
    cout << "1. " GreenOpen "I know." Reset << endl;
    cout << "2. " RedOpen "I do not konw." Reset << endl;
    
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
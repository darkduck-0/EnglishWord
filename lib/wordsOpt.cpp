#include "wordsOpt.h"

std::mt19937 gen(std::random_device{}());
std::random_device rd;

using std::cout, std::cin, std::endl;
using std::string, std::vector;

static vector<const string *> opts, errWordTemp, errWordTotal, chis;
static string noRightOpt = GreenOpen "No correct option.\n" Reset;
static string misMemOpt = RedOpen "Honestly, I misremembered.\n" Reset;
static int rightOpt;
static uint32_t errWordCount;

extern size_t optSize; // from start

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

    const string *t = opts[rightOpt];
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
    int userOpt;
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
        targetWord->coutLevel() << endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(750));
        return FINI;
    }

    // ++errWordCount;

    cout << Clear;
    cout << RedOpen "wrong." Reset;
    targetWord->coutLevel() << '\n';

    cout << targetWord->eng << ": " << targetWord->chi << '\n';
    cout << "I know." << endl;

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
#include "winbuild.h"
#include "fileOrg.h"
#include "word.h"
#include "wordsOpt.h"
#include "wordsOrg.h"
#include "sign.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include "easyConsole.h"
#include <thread>

#define optNum 4

using std::cout, std::cin, std::endl;
using std::ifstream, std::ofstream;
using std::vector, std::string;

string fileName;
extern vector<Word> words;
extern size_t optSize;

int main(int argc, const char *argv[])
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    if (argc < 2)
    {
        cout << RedOpen "usage: start file" Reset << endl;
        return UERR;
    }

    fileName = argv[1];

    int total = loadFile(fileName, words);
    if (total < optSize)
    {
        cout << RedOpen "Too few words.\n" Reset << endl;
        return UERR;
    }
    initOrg();
    initOpt();

    for (; maintain();)
    {
        switch (know())
        {
        case FINI:
            break;
        case UERR:
            goto wrong;
        case QUIT:
            goto quit;
        }
        randomOpt();
        showOpt();

        switch (judge())
        {
        case QUIT:
            goto quit;
        case FINI:
            break;
        case UERR:
            goto wrong;
        }
        correct();
        continue;
    wrong:
        wrong();
    }
quit:
    saveFile(fileName, words);
    return FINI;
}

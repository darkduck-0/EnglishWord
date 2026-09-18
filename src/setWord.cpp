#include "fileOrg.h"
#include <unistd.h>
#include "sign.h"
#include "easyConsole.h"
#include <ctime>

using std::cout, std::cin, std::endl;
using std::ifstream, std::ofstream;
using std::string, std::vector;

extern vector<Word> words;
string fileName;
int16_t level;

void reset(Word &w)
{
    w.lastTime = w.nextTime = 0;
    w.level = 0;
}

void set(Word &w)
{
    w.level = level;
    w.lastTime = w.nextTime = time(0);
}

sign option(void(f)(Word &))
{
    int wordNum;
    if ((wordNum = loadFile(fileName, words)) == -1)
    {
        cout << RedOpen "Can not open file: " << fileName << Reset << endl;
        return FERR;
    }
    cout << GreenOpen "Read " << wordNum << "words." << endl;

    for (auto &i : words)
        f(i);

    string tempFile = fileName + ".tmp";
    if ((wordNum = saveFile(tempFile, words)) == -1)
    {
        cout << RedOpen << "Can not creat file: " << tempFile << Reset << endl;
        return FERR;
    }
    cout << GreenOpen "Write " << wordNum << "words." Reset << endl;

    remove(fileName.c_str());
    rename(tempFile.c_str(), fileName.c_str());
    return FINI;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cout << RedOpen "usage: set [-r/s:level] file" Reset << endl;
        return UERR;
    }

    bool resetMod = false;
    bool setMod = true;
    int opt;
    while ((opt = getopt(argc, argv, "rs:")) != -1)
    {
        switch (opt)
        {
        case 'r':
            resetMod = true;
            setMod = false;
            break;
        case 's':
            level = std::stoi(optarg);
            resetMod = false;
            setMod = true;
            break;
        case '?':
            cout << "unknown command.\n";
            return UERR;
        default:
            break;
        }
    }

    if (resetMod)
    {
        for (int i = optind; i < argc; ++i)
        {
            fileName = argv[i];
            option(reset);
        }
    }

    else if (setMod)
    {
        for (int i = optind; i < argc; ++i)
        {
            fileName = argv[i];
            option(set);
        }
    }
    else
    {
        cout << "no command.\n";
        return UERR;
    }

    return FINI;
}
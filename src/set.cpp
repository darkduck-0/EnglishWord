#include "fileOpt.h"
#include <unistd.h>

using std::cout, std::cin, std::endl;
using std::ifstream, std::ofstream;
using std::string, std::vector;

vector<Word> wordTable;
string fileName;
int16_t level;

void reset()
{
    for (auto &i : wordTable)
        i.reset();
}

void set()
{
    for (auto &i : wordTable)
    {
        i.level = level;
        i.reviewNow();
    }
}

sign option(void(f)())
{
    ifstream inFile(fileName);
    if (!inFile.is_open())
    {
        cout << "can not open file: " << fileName << endl;
        return FERR;
    }
    cout << "read " << loadFile(inFile, wordTable) << " words in file: " << fileName << ".\n";
    inFile.close();

    f();

    string tempFile = fileName + ".tmp";
    ofstream outFile(tempFile);
    if (!outFile.is_open())
    {
        cout << "can not creat file: " << tempFile << endl;
        return FERR;
    }
    cout << "write " << saveFile(outFile, wordTable) << " words in file: " << fileName << ".\n";

    outFile.close();
    remove(fileName.c_str());
    rename(tempFile.c_str(), fileName.c_str());
    return FINI;
}

int main(int argc, char *argv[])
{
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
#include "sign.h"
#include "fileOpt.h"
#include <unistd.h>

using std::cout, std::cin, std::endl;
using std::ifstream, std::ofstream;
using std::string, std::vector;

int main(int argc, char *argv[])
{
    bool append = false;
    bool screen = true;
    bool detail = false;

    int opt;
    string fileName;
    while ((opt = getopt(argc, argv, "af:d")) != -1)
    {
        switch (opt)
        {
        case 'a':
            append = true;
            break;
        case 'f':
            fileName = optarg;
            screen = false;
            break;
        case 'd':
            detail = true;
            break;
        case '?':
        cout << "usage: typeIn -a/f/d [source] destination\n";
        return UERR;
        default:
            break;
        }
    }

    vector<Word> words;
    if (screen)
    {
        importWord(cin, words);
    }
    else
    {
        ifstream inFile(fileName);
        if (!inFile.is_open())
        {
            cout << "can not open file: " << fileName << ".\n";
            return FERR;
        }
        importWord(inFile, words);
    }

    if (detail)
    {
        for (auto &i : words)
            cout << i;
        cout << "read " << words.size() << " words.\n";
    }

    ofstream outFile;
    fileName = argv[optind];
    outFile.open(fileName, append ? std::ios::app : std::ios::out);

    if (!outFile.is_open())
    {
        cout << "can not open file: " << fileName << ".\n";
        return FERR;
    }
    saveFile(outFile, words);

    return FINI;
}
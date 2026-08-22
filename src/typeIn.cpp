#include "sign.h"
#include "fileOpt.h"

using std::cout, std::cin, std::endl;
using std::ifstream, std::ofstream;
using std::string, std::vector;

int main(int argc, char *argv[])
{
    if (argc < 3 || argc > 4)
    {
        cout << "usage: typeIn -a/s/d [source] destination\n";
        return UERR;
    }

    bool append = false;
    bool screen = false;
    bool detail = false;
    string cmd = argv[1];
    for (auto c : cmd)
    {
        switch (c)
        {
        case '-':
        default:
            break;
        case 'a':
            append = true;
            break;
        case 's':
            screen = true;
            break;
        case 'd':
            detail = true;
            break;
        }
    }

    vector<Word> words;
    string outFileName;
    if (screen)
    {
        importWord(cin, words);
        outFileName = argv[2];
    }
    else
    {
        outFileName = argv[3];
        ifstream inFile(argv[2]);
        if (!inFile.is_open())
        {
            cout << "can not open file: " << argv[2] << ".\n";
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
    if (append)
    {
        outFile.open(outFileName, std::ios::app);
    }
    else
    {
        outFile.open(outFileName);
    }

    if (!outFile.is_open())
    {
        cout << "can not open file: " << outFileName << ".\n";
        return FERR;
    }
    saveFile(outFile, words);

    return FINI;
}
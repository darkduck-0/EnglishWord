#include "winbuild.h"
#include "sign.h"
#include "fileOrg.h"
#include <unistd.h>
#include "easyConsole.h"

using std::cout, std::cin, std::endl;
using std::ifstream, std::ofstream;
using std::string, std::vector;

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cout << RedOpen "usage: typeIn [-adf:file] desFile" Reset << endl;
        return UERR;
    }

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
            cout << RedOpen "usage: typeIn [-adf:file] desFile" Reset << endl;
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
            cout << RedOpen "Can not open file: " << fileName << Reset << endl;
            return FERR;
        }
        importWord(inFile, words);
    }

#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    cout << "utf-8 enable\n";
#endif

    if (detail)
    {
        for (auto &i : words)
            cout << i;
        cout << GreenOpen "Read " << words.size() << " words." Reset << endl;
    }

    ofstream outFile;
    fileName = argv[optind];
    outFile.open(fileName, append ? std::ios::app : std::ios::out);

    int count;
    if ((count = saveFile(fileName, words)) == -1)
    {
        cout << RedOpen "Can not open file: " << fileName << Reset << endl;
        return FERR;
    }
    if (detail)
        cout << GreenOpen "Write " << count << " words." Reset << endl;

    return FINI;
}
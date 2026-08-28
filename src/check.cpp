#include "winbuild.h"
#include "word.h"
#include "fileOrg.h"
#include "sign.h"
#include "easyConsole.h"

using std::cout, std::endl;

int main(int argc, const char *argv[])
{
    if (argc < 2)
    {
        cout << RedOpen "usage: check file" Reset << endl;
        return UERR;
    }

#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    std::vector<Word> words;
    words.reserve(1024);
    for (int i = 1; i < argc; ++i)
    {
        if (loadFile(argv[i], words) == -1)
        {
            cout << RedOpen "Can not open file: " << argv[i] << endl;
            continue;
        }
        cout << argv[i] << ":\n";
        for (auto &k : words)
            cout << k;
        cout << GreenOpen "Read " << words.size() << " words." << endl;
    }

    return FINI;
}
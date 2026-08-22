#include "word.h"
#include "fileOpt.h"
#include "sign.h"

using std::cout, std::endl;

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cout << "usage: check file\n";
        return UERR;
    }

    std::vector<Word> words;
    words.reserve(1024);
    std::ifstream file;
    for (int i = 1; i < argc; ++i)
    {
        file.open(argv[i]);
        if (!file.is_open())
        {
            cout << "can not open file: " << argv[i] << ".\n";
            file.close();
            continue;
        }

        cout << argv[i] << ":\n";
        words.clear();
        loadFile(file, words);
        for (auto &k : words)
            cout << k;
        cout << words.size() << " words.\n";
        file.close();
    }

    return FINI;
}
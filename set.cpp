#include "fileOpt.h"

using std::cout, std::cin, std::endl;
using std::ifstream, std::ofstream;
using std::string, std::vector;

vector<Word> wordTable;
string fileName;
int16_t level;

int main(int argc, char *argv[])
{
    /*
    if (argc < 3)
    {
        cout << "usage: file level\n";
        return UERR;
    }

    fileName = argv[1];
    level = std::stoi((string)(argv[2]));
    if (level < 0 || level > 12)
    {
        cout << "invalid level.\n";
        return UERR;
    }
    */
    cin >> fileName >> level;
    ifstream inFile(fileName);
    if (!inFile.is_open())
    {
        cout << "can not open file: " << fileName << endl;
        return FERR;
    }
    cout << "read " << loadFile(inFile, wordTable) << " words.\n";

    for (auto &i : wordTable)
    {
        i.level = level;
        i.reviewNow();
    }
    inFile.close();

    string tempFile = fileName + ".tmp";
    ofstream outFile(tempFile);
    if (!outFile.is_open())
    {
        cout << "can not creat file: " << tempFile << endl;
        return FERR;
    }
    cout << "write " << saveFile(outFile, wordTable) << " words.\n";

    remove(fileName.c_str());
    rename(tempFile.c_str(), fileName.c_str());

    return FINI;
}
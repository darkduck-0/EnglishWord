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


using std::cout, std::cin, std::endl;
using std::vector, std::string;
using std::ifstream, std::ofstream;


sign startInit();


string fileName;
ifstream inFile;
ofstream outFile;
std::stringstream inFileStream;
vector<Word> words;


int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cout << "usage: start file" << endl;
        return UERR;
    }

    fileName = argv[1];
    inFile.open(fileName);
    if (!inFile.is_open())
    {
        cout << RedOpen "Can not open file: " << fileName << "." Reset << endl;
        return FERR;
    }

    inFileStream << inFile.rdbuf();
    inFile.close();
    loadFile(inFileStream, words);

    if (startInit())
        return UERR;
    
    while (true)
    {
    }
    
}


sign startInit()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8); 
    SetConsoleCP(CP_UTF8);
#endif

    cout << HideCursor;
    initOrg();
    initOpt();

    
}
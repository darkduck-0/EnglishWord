#ifndef RECITIGN
#define RECITING
#include <string>
#include <iostream>
#include <vector>
#include <random>
#include <thread>
#include <algorithm>
#include "word.h"
#include "sign.h"

using std::cout, std::cin, std::endl;
using std::string, std::vector;

auto compare = [](Word *x, Word *y)
{ return *x > *y; };

std::mt19937 gen(std::random_device{}());
std::random_device rd;

class reciting
{
private:
    vector<Word> words;
    vector<Word *> New, Old;
    vector<string *> chis, qus;
    uint32_t ritChs;
    uint32_t errCount;
    string fileName;
    uint32_t qusNum;
    uint32_t errMax;

public:
    reciting(string fileName, uint32_t errMax, uint32_t qusNum);
    sign know();
    sign init();
    sign ranOpt();
    sign judge();
    sign collate();
    sign save();
    void opt();
};

#endif
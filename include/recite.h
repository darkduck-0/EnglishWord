#ifndef RECITE
#define RECITE

#ifdef _WIN32
#include <windows.h>
#endif

#include "word.h"
#include <algorithm>
#include "fileOpt.h"
#include <random>
#include <thread>
#include <chrono>

using std::cout, std::cin, std::endl;
using std::ifstream, std::ofstream;
using std::string, std::vector;

sign know();
sign init();
sign ranOpt();
sign judge();
sign collate();
sign save();
void opt();
auto compare = [](Word *x, Word *y)
{ return *x > *y; };

std::mt19937 gen(std::random_device{}());
std::random_device rd;
vector<Word> words;
vector<Word *> New, Old;
vector<string *> chis;
vector<string *> qus;
uint32_t ritChs;
uint32_t errCount;
string fileName;

#endif
#ifndef WORDSOPT
#define WORDSOPT

#include <string>
#include <vector>
#include <random>
#include <thread>
#include <algorithm>
#include "word.h"
#include "sign.h"
#include "easyConsole.h"

void initOpt();
void randomOpt(std::string *);
void showOpt(std::string *);

sign know(Word *);
sign judge(Word *);

#endif
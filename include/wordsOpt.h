#ifndef WORDSOPT
#define WORDSOPT

#include <string>
#include "word.h"
#include "sign.h"

void initOpt();
void randomOpt(std::string *);
void showOpt(std::string *);

sign know(Word *);
sign judge(Word *);

#endif
#ifndef WORDSORG
#define WORDSORG


#include <vector>
#include <string>
#include "word.h"
#include <algorithm>
#include "sign.h"
#include <chrono>


static auto compare = [](Word *x, Word *y)
{ return *x > *y; };


void initOrg();
void readyMove();
void waitingMove();


#endif
#ifndef FILEOPT
#define FILEOPT
#include "word.h"
#include "sign.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

int loadFile(std::ifstream &, std::vector<Word> &);
// check valid, quit,
int saveFile(std::ofstream &, std::vector<Word> &);
// check writable
int importWord(std::istream &, std::vector<Word> &);
// no check

#endif
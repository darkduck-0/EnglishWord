#ifndef FILEOPT
#define FILEOPT
#include "word.h"
#include "sign.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

// the functions are not check whether the file is valid.
// return the number of processed words.
int loadFile(std::ifstream &, std::vector<Word> &);
int saveFile(std::ofstream &, std::vector<Word> &);
int importWord(std::istream &, std::vector<Word> &);

#endif
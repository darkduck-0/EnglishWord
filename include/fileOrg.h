#ifndef FILEOPT
#define FILEOPT

#include "word.h"
#include "sign.h"
#include <string>
#include <vector>
#include <fstream>

// the functions are not check whether the file is valid.
// return the number of processed words.
int loadFile(std::string &fileName, std::vector<Word> &words);
int saveFile(std::string &fileName, std::vector<Word> &words);
int importWord(std::istream &, std::vector<Word> &);

#endif
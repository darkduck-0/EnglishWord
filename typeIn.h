#ifndef typeIn
#define typeIn

#include <iostream>
#include <fstream>
#include "word.h"
#include <vector>

int saveToNew(std::vector<Word> &v);
int saveToExist(std::vector<Word> &v);
int readFromFile(std::vector<Word> &v);
int readFromKey(std::vector<Word> &v);

#endif
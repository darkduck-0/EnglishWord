#ifndef typeIn
#define typeIn

#include <iostream>
#include <fstream>
#include "word.cpp"
#include <vector>

int saveToNew();
int saveToExist();
int readFromFile();
int readFromKey();

std::vector<Word> wordTable;

#endif

// 我迟早要tm把 word.cpp 改为word.h
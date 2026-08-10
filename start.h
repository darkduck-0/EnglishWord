#include <fstream>
#include <iostream>
#include <vector>
#include "word.cpp"
#include <algorithm>
#include <random>
#include <ctime>

class Settings
{
public:
    uint32_t men;
    uint32_t cdw;
};

int start(std::vector<Word>);
int load(std::vector<Word>);
int init();
int ranopt(std::vector<std::string *> &qus, uint &right);
int choise(uint real, uint chs, bool init);
int collate();
int exit();
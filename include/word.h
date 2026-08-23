#ifndef WORD
#define WORD

#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>

class Word
{
public:
    std::string eng;
    std::string chi;
    uint64_t lastTime;
    int16_t level;
    uint64_t nextTime;

    Word(std::string, std::string, uint64_t, int16_t, uint64_t);
    void initTime();
    void updateTime();
    void reviewNow();
    void reset();
    void upGrade();
    bool deGrade();
    void write(std::ofstream &);
    bool operator<(const Word &other) const;
    bool operator>(const Word &other) const;

private:
    friend std::ostream &operator<<(std::ostream &os, const Word &p);
    friend std::ofstream &operator<<(std::ofstream &os, const Word &p);
    friend std::ifstream &operator>>(std::ifstream &is, Word &p);
};

#endif
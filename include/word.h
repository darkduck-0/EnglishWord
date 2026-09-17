#ifndef WORD
#define WORD

#include <string>
#include <iostream>
#include <fstream>

class Word
{
    friend std::ostream &operator<<(std::ostream &os, const Word &p);
    friend std::ofstream &operator<<(std::ofstream &os, const Word &p);
    void friend reset(Word &);
    void friend set(Word &);
    // wordsOpt

public:
    const std::string eng;
    const std::string chi;
    int16_t errTmp;

    Word(std::string, std::string, int16_t = 0,
         time_t = 0, time_t = 0, int16_t = 0);
    void updateTime();
    void updateTime(size_t level);
    std::ostream &coutLastTime() const;
    std::ostream &coutNextTime() const;
    std::ostream &coutLevel() const;
    bool timeUp() const;
    bool isNew() const;
    bool upGrade(int16_t d = 1);
    bool deGrade(int16_t d = 1);
    bool operator<(const Word &other) const;
    bool operator>(const Word &other) const;

private:
    int16_t level;
    time_t lastTime;
    time_t nextTime;
};

#endif
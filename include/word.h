#ifndef WORD
#define WORD

#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <chrono>

class Word
{
    friend std::ostream &operator<<(std::ostream &os, const Word &p);
    friend std::ofstream &operator<<(std::ofstream &os, const Word &p);

public:
    const std::string eng;
    const std::string chi;

    Word(std::string, std::string, time_t, int16_t, time_t);
    void updateTime();
    void updateTime(size_t level);
    void reset();
    std::ostream &coutLastTime() const;
    std::ostream &coutNextTime() const;
    std::ostream &coutLevel() const;
    bool timeUp() const;
    bool upGrade(int16_t d = 1);
    bool deGrade(int16_t d = 1);
    bool operator<(const Word &other) const;
    bool operator>(const Word &other) const;

private:
    time_t lastTime;
    int16_t level;
    time_t nextTime;
};

#endif
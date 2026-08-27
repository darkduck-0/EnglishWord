#include "word.h"
#define MAXLEVEL 11
#define MINUTE 60
#define HOUR 60 * MINUTE
#define DAY 24 * HOUR

const static uint64_t levelSwitch[MAXLEVEL] = {
    0,
    MINUTE,
    30 * MINUTE,
    HOUR,
    4 * HOUR,
    DAY,
    3 * DAY,
    7 * DAY,
    15 * DAY,
    30 * DAY,
    60 * DAY,
};

Word::Word(std::string e, std::string c, time_t ct = 0,
           int16_t l = 0, time_t nt = 0)
    : eng(e), chi(c), lastTime(ct), level(l), nextTime(nt) {}

void Word::reset()
{
    lastTime = nextTime = 0;
    level = 0;
}

bool Word::upGrade(int16_t delta)
{
    level += delta;
    bool result = level > MAXLEVEL;
    level = result ? MAXLEVEL : level;
    return result;
}

bool Word::deGrade(int16_t delta)
{
    level -= delta;
    bool result = level < 0;
    level = result ? 0 : level;
    return result;
}

void Word::updateTime()
{
    lastTime = time(0);
    nextTime = lastTime + levelSwitch[level];
}

void Word::updateTime(size_t l)
{
    lastTime = time(0);
    nextTime = lastTime + levelSwitch[l];
}

bool Word::operator<(const Word &other) const
{
    return nextTime < other.nextTime;
}

bool Word::operator>(const Word &other) const
{
    return nextTime > other.nextTime;
}

std::ostream &operator<<(std::ostream &os, const Word &p)
{
    os << p.eng << '\t' << p.chi << '\t';
    p.coutLastTime() << '\t' << p.level << '\t';
    p.coutNextTime() << '\n';
    return os;
}

std::ofstream &operator<<(std::ofstream &os, const Word &p)
{
    os << p.eng << '\t' << p.chi << '\t';
    os.write(reinterpret_cast<const char *>(&p.lastTime), sizeof(p.lastTime));
    os.write(reinterpret_cast<const char *>(&p.level), sizeof(p.level));
    os.write(reinterpret_cast<const char *>(&p.nextTime), sizeof(p.nextTime));
    os << '\n';
    return os;
}

std::ostream &Word::coutLastTime() const
{
    std::tm *tm = std::localtime(&lastTime);
    std::cout << std::put_time(tm, "%Y-%m-%d %H:%M:%S");
    return std::cout;
}

std::ostream &Word::coutNextTime() const
{
    std::tm *tm = std::localtime(&nextTime);
    std::cout << std::put_time(tm, "%Y-%m-%d %H:%M:%S");
    return std::cout;
}

std::ostream &Word::coutLevel() const
{
    std::cout << "level: " << level;
    return std::cout;
}

bool Word::timeUp() const
{
    return time(0) > nextTime;
}
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

Word::Word(std::string e, std::string c, uint64_t ct = 0,
           int16_t l = 0, uint64_t nt = 0)
    : eng(e), chi(c), lastTime(ct), level(l), nextTime(nt) {}

void Word::initTime()
{
    lastTime = time(0);
    nextTime = lastTime;
}

void Word::reset()
{
    lastTime = nextTime = 0;
    level = 0;
}

void Word::upGrade()
{
    ++level;
    level = level > MAXLEVEL ? MAXLEVEL : level;
}

bool Word::deGrade()
{
    --level;
    bool result = level < 0;
    level = result ? 0 : level;
    return result;
}

void Word::updateTime()
{
    lastTime = time(0);
    nextTime = lastTime + levelSwitch[level];
}

void Word::reviewNow()
{
    nextTime = lastTime = time(0);
}

void Word::write(std::ofstream &os)
{
    os.write(eng.data(), eng.size());
    os.write("\t", 1);
    os.write(chi.data(), chi.size());
    os.write("\t", 1);
    os.write(reinterpret_cast<const char *>(&lastTime), sizeof(lastTime));
    os.write(reinterpret_cast<const char *>(&level), sizeof(level));
    os.write(reinterpret_cast<const char *>(&nextTime), sizeof(nextTime));
    os.write("\n", 1);
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
    os << p.eng << '\t';
    os << p.chi << '\t';
    os << p.lastTime << '\t';
    os << p.level << '\t';
    os << p.nextTime << '\n';
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

std::ifstream &operator>>(std::ifstream &is, Word &p)
{
    is >> p.eng >> p.chi;
    is.ignore();
    is.read(reinterpret_cast<char *>(&p.lastTime), sizeof(p.lastTime));
    is.read(reinterpret_cast<char *>(&p.level), sizeof(p.level));
    is.read(reinterpret_cast<char *>(&p.nextTime), sizeof(p.nextTime));
    return is;
}
#include "word.h"
#define MAXLEVEL 11
const static uint64_t levelSwitch[MAXLEVEL] = {
    0,
    10,
    30,
    60,
    300,
    600,
    30 * 60,
    1 * 3600,
    2 * 3600,
    4 * 3600,
    24 * 3600,
};

Word::Word(std::string e, std::string c, uint64_t ct = 0,
           int16_t l = 0, uint64_t nt = 0)
    : eng(e), chi(c), currentTime(ct), level(l), nextTime(nt) {}

void Word::initTime()
{
    currentTime = time(0);
    nextTime = currentTime;
}

void Word::upGrade()
{
    ++level;
    level = level > MAXLEVEL ? MAXLEVEL : level;
    updateTime(); // 要不要这一行？
}

bool Word::deGrade()
{
    --level;
    bool result = level < 0;
    level = result ? 0 : level;
    updateTime(); // 要不要这一行？
    return result;
}

void Word::updateTime()
{
    currentTime = time(0);
    nextTime = currentTime + levelSwitch[level];
}

void Word::reviewNow()
{
    nextTime = currentTime = time(0);
}

void Word::write(std::ofstream &os)
{
    os.write(eng.data(), eng.size());
    os.write("\t", 1);
    os.write(chi.data(), chi.size());
    os.write("\t", 1);
    os.write(reinterpret_cast<const char *>(&currentTime), sizeof(currentTime));
    os.write(reinterpret_cast<const char *>(&level), sizeof(level));
    os.write(reinterpret_cast<const char *>(&nextTime), sizeof(nextTime));
    os.write("\n", 1);
}

void Word::read(std::ifstream &os)
{
    os >> eng;
    os >> chi;
    os.ignore();
    os.read(reinterpret_cast<char *>(&currentTime), sizeof(currentTime));
    os.read(reinterpret_cast<char *>(&level), sizeof(level));
    os.read(reinterpret_cast<char *>(&nextTime), sizeof(nextTime));
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
    os << p.currentTime << '\t';
    os << p.level << '\t';
    os << p.nextTime << '\n';
    return os;
}

std::ofstream &operator<<(std::ofstream &os, const Word &p)
{
    os << p.eng << '\t' << p.chi << '\t';
    os.write(reinterpret_cast<const char *>(&p.currentTime), sizeof(p.currentTime));
    os.write(reinterpret_cast<const char *>(&p.level), sizeof(p.level));
    os.write(reinterpret_cast<const char *>(&p.nextTime), sizeof(p.nextTime));
    os << '\n';
    return os;
}

std::ifstream &operator>>(std::ifstream &is, Word &p)
{
    is >> p.eng >> p.chi;
    is.ignore();
    is.read(reinterpret_cast<char *>(&p.currentTime), sizeof(p.currentTime));
    is.read(reinterpret_cast<char *>(&p.level), sizeof(p.level));
    is.read(reinterpret_cast<char *>(&p.nextTime), sizeof(p.nextTime));
    return is;
}
// 把 currentTime 改名为 lastTime
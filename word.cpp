#include "word.h"

const static uint64_t levelSwitch[11] = {
    60,
    600,
    3600,
    4 * 3600,
    24 * 3600,
    3 * 24 * 3600,
    7 * 24 * 3600,
    15 * 24 * 3600,
    30 * 24 * 3600,
    60 * 24 * 3600,
    120 * 24 * 3600};

Word::Word(std::string e, std::string c, uint64_t ct = 0,
           int16_t l = 0, uint64_t nt = 0)
    : eng(e), chi(c), currentTime(ct), level(l), nextTime(nt) {}

void Word::updateTime()
{
    currentTime = time(0);
    nextTime = currentTime + levelSwitch[level];
}

void Word::write(std::ofstream &file)
{
    file.write(eng.data(), eng.size());
    file.write("\t", 1);
    file.write(chi.data(), chi.size());
    file.write("\t", 1);
    file.write(reinterpret_cast<const char *>(&currentTime), sizeof(currentTime));
    file.write(reinterpret_cast<const char *>(&level), sizeof(level));
    file.write(reinterpret_cast<char *>(&nextTime), sizeof(nextTime));
    file.write("\n", 1);
}

void Word::read(std::ifstream &file)
{
    file >> eng;
    file >> chi;
    file.ignore();
    file.read(reinterpret_cast<char *>(&currentTime), sizeof(currentTime));
    file.read(reinterpret_cast<char *>(&level), sizeof(level));
    file.read(reinterpret_cast<char *>(&nextTime), sizeof(nextTime));
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
    os << p.eng << ": " << p.chi << "\n\tlastTime: " << p.currentTime << " level: " << p.level << " nextTime: " << p.nextTime << '\n';
    return os;
}
// 把 currentTime 改名为 lastTime
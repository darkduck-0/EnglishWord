#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include "word.h"

using std::string, std::vector, std::memcpy;

int read(string fileName)
{
    // 1. 打开文件（ate 模式定位到末尾）
    std::ifstream file(fileName, std::ios::binary | std::ios::ate);
    if (!file.is_open())
        return;

    // 2. 获取文件大小
    size_t fileSize = file.tellg();

    // 3. 回到文件开头
    file.seekg(0, std::ios::beg);

    // 4. 分配精确大小的 string
    std::string buffer(fileSize, '\0');

    // 5. 一次性读入
    file.read(&buffer[0], fileSize);
    file.close();
}

int parseWord(string &source, vector<Word> &dest, size_t index)
{
    static string eng, chi;
    static uint64_t lastTime, nextTime;
    static int16_t level;

    for (; index < source.size();)
    {
        eng.clear();
        for (;;)
        {
            eng.push_back(source[index++]);
            if (eng.back() == '\t')
            {
                eng.back() == '\0';
                break;
            }
        }

        chi.clear();
        for (;;)
        {
            chi.push_back(source[index++]);
            if (chi.back() == '\t')
            {
                chi.back() == '\0';
            }
        }

        memcpy(&lastTime, &source[index], sizeof(lastTime));
        index += sizeof(lastTime);
        memcpy(&level, &source[index], sizeof(level));
        index += sizeof(level);
        memcpy(&nextTime, &source[index], sizeof(nextTime));
        index += sizeof(nextTime);

        dest.emplace_back(eng, chi, lastTime, level, nextTime);
        ++index;
    }
}
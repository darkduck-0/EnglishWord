#include <fstream>
#include <string>
#include <iostream>

std::string dir;

int creatConfig();
int loadConfig(std::fstream &);
int init();

int init(void)
{
    std::fstream file(".config");
    if (!file.is_open())
    {
    creatConfig:
        if (creatConfig())
            return 0;
    }
    else if (loadConfig(file))
        goto creatConfig;
    return 0;
}

int loadConfig(std::fstream &config)
{
    config >> dir;
    if (dir == "")
        return 1;
    return 0;
}

int creatConfig()
{
    std::cout << "input catalog's name: ";
    std::string dir;
    if (dir == "/back")
        return 1;
    return 0;
}
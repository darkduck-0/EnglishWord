#include <fstream>
#include <string>
#include <iostream>

class config
{
public:
    uint maxErrNum;
    uint optionNum;
    std::string catalog;
    config(std::string s) : catalog(s), optionNum(4), maxErrNum(1) {}

private:
} configs;

std::string dir;

int creatConfig();
int loadConfig(std::ifstream &);
int init();

int init(void)
{
    std::ifstream file(".config");
    if (!file.is_open())
    {
    creatConfig:
        if (creatConfig())
            return -2;
    }
    else if (loadConfig(file))
        goto creatConfig;
    return 0;
}

int loadConfig(std::ifstream &config)
{
    config >> dir;
    if (dir == "")
        return 1;
    else
    {
        // todo;
    }
    return 0;
}

int creatConfig()
{
    std::ofstream config(".config");
    if (!config.is_open())
    {
        std::cout << "can not creat file: .config\n";
        return -2;
    }
    std::cout << "input catalog's name: ";
    std::string dir;
    std::cin >> dir;
    if (dir == "/back")
        return 0;
    else
    {
        config << dir;
    }
    return 0;
}

#ifndef nobug
int main()
{
    init();
}
#endif
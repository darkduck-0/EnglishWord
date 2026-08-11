#include "typeIn.h"

enum sign
{
    UERR,
    FERR,
    QUIT,
    FINI,
    REBOOT
};

int saveToNew()
{
    std::cout << "The file name: ";
    std::string name;
    std::cin >> name;
    if (name == "/back")
        return QUIT;
    std::ifstream ifile(name);
    if (ifile.is_open())
    {
        std::cout << "The file: " << name << " exist.\n";
        return REBOOT;
    }
    ifile.close();
    std::ofstream file(name, std::ios::binary);
    for (auto &i : wordTable)
        file << i;
    return FINI;
}

int saveToExist()
{
    std::cout << "The file name: ";
    std::string name;
    std::cin >> name;
    if (name == "\back")
        return QUIT;
    std::ofstream file(name, std::ios::app);
    if (!file.is_open())
    {
        std::cout << "can not open file: " << name << std::endl;
        return REBOOT;
    }
    for (auto &i : wordTable)
        file << i;
    return FINI;
}

int readFromFile()
{
    std::cout << "The file address: ";
    std::string address;

    std::cin >> address;
    if (address == "/back")
        return QUIT;

    // 添加文件大小限制
    std::ifstream file(address);
    if (!file.is_open())
    {
        std::cout << "can not open file: " << address << std::endl;
        return REBOOT;
    }
    std::string eng, chi;
    while (file >> eng >> chi)
    {
        wordTable.emplace_back(eng, chi);
    }
    std::cout << address << " readed.\n";
    return FINI;
}

int readFromKey()
{
    std::string eng, chi;
    while (true)
    {
        std::cin >> eng;
        if (eng == "/back")
            break;
        std::cin >> chi;
        wordTable.emplace_back(eng, chi);
    }
    return FINI;
}

int shell()
{
    std::string cmd;
manu1:
    std::cout << "choose which way to type in:\n";
    std::cout << "1.From file\n";
    std::cout << "2.From keyboard\n";
    std::cin >> cmd;
    if (cmd == "/back")
    {
        return FINI;
    }
    else if (cmd == "1")
    {
    rdf:
        switch (readFromFile())
        {
        case QUIT:
            goto manu1;
        case REBOOT:
            goto rdf;
        case FINI:
        default:
            break;
        }
    }
    else if (cmd == "2")
    {
        switch (readFromKey() == 1)
        {
        case FINI:
        default:
            break;
        }
    }
    else
    {
        std::cout << "unknown command: " << cmd << std::endl;
        goto manu1;
    }

manu2:
    std::cout << "choose where to save:\n";
    std::cout << "1.new file\n";
    std::cout << "2.old file\n";

    std::cin >> cmd;
    if (cmd == "/back")
    {
        wordTable.clear();
        goto manu1;
    }
    else if (cmd == "1")
    {
    stn:
        switch (saveToNew())
        {
        case QUIT:
            goto manu2;
        case REBOOT:
            goto stn;
        case FINI:
        default:
            break;
        }
    }
    else if (cmd == "2")
    {
    ste:
        switch (saveToExist())
        {
        case QUIT:
            goto manu2;
        case REBOOT:
            goto ste;
        case FINI:
        default:
            break;
        }
    }
    else
    {
        std::cout << "unknown command: " << cmd << std::endl;
        goto manu2;
    }
    return FINI;
}

#ifndef nobug
int main()
{
    shell();
    return 0;
}
#endif

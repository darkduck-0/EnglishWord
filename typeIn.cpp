#include "typeIn.h"

int saveToNew()
{
    std::cout << "The file name: ";
    std::string name;
    std::cin >> name;
    std::ifstream ifile(name);
    if (ifile.is_open())
    {
        std::cout << "The file: " << name << " exist.\n";
        return 1;
    }
    ifile.close();
    std::ofstream file(name, std::ios::binary);
    for (auto &i : wordTable)
        i.write(file);
    return 0;
}

int saveToExist()
{
    std::cout << "The file name: ";
    std::string name;
    std::cin >> name;
    std::ofstream file(name, std::ios::app);
    if (!file.is_open())
    {
        std::cout << "error\n";
        return -1;
    }
    for (auto &i : wordTable)
        i.write(file);
    return 0;
}

int readFromFile()
{
    std::cout << "The file address: ";
    std::string address;

    std::cin >> address;
    if (address == "/back")
        return -1;

    // 添加文件大小限制
    std::ifstream file(address);
    if (!file.is_open())
        return 1;
    std::string eng, chi;
    while (!file.eof())
    {
        file >> eng >> chi;
        wordTable.emplace_back(eng, chi);
    }
    return 0;
}

int readFromKey()
{
    std::cout << "type /end to stop\n";
    std::string eng, chi;
    while (true)
    {
        std::cin >> eng;
        if (eng == "/end")
            break;
        std::cin >> chi;
        wordTable.emplace_back(eng, chi);
    }
    // debug
    for (int i = 0; i < wordTable.size(); ++i)
    {
        std::cout << i << "\t";
        std::cout << wordTable[i];
    }
    // debug
    return 0;
}

int main()
{
    readFromFile();
    saveToNew();

    return 0;
}
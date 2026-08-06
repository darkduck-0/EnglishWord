#include <iostream>
#include <fstream>
#include "word.cpp"
#include <vector>

int saveToExist(std::vector<Word>);
int saveToNew(std::vector<Word>);

int saveToNew(std::vector<Word> v)
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
    for (auto &i : v)
        i.write(file);
    return 0;
}

int saveToExist(std::vector<Word> v)
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
    for (auto &i : v)
        i.write(file);
    return 0;
}

int readFromFile(std::vector<Word> &v)
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
        v.emplace_back(eng, chi);
    }
    return 0;
}

int readFromKey(std::vector<Word> &v)
{
    std::cout << "type /end to stop\n";
    std::string eng, chi;
    while (true)
    {
        std::cin >> eng;
        if (eng == "/end")
            break;
        std::cin >> chi;
        v.emplace_back(eng, chi);
    }
    // debug
    for (int i = 0; i < v.size(); ++i)
    {
        std::cout << i << "\t";
        std::cout << v[i];
    }
    // debug
    return 0;
}

int main()
{
    std::vector<Word> v;
    readFromFile(v);
    // debug
    for (int i = 0; i < v.size(); ++i)
    {
        std::cout << i << "\t";
        std::cout << v[i];
    }
    // debug
    saveToNew(v);

    return 0;
}
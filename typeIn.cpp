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
        file << i;
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
        std::cout << "can not open file: " << name << "\n";
        return 1;
    }
    for (auto &i : wordTable)
        file << i;
    return 0;
}

int readFromFile()
{
    std::cout << "The file address: ";
    std::string address;

    std::cin >> address;
    if (address == "/back")
        return 1;

    // 添加文件大小限制
    std::ifstream file(address);
    if (!file.is_open())
    {
        std::cout << "can not open file: " << address << std::endl;
        return 1;
    }
    std::string eng, chi;
    while (file >> eng >> chi)
    {
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
    return 0;
}

int main()
{
    /*
    uint choose = 0;
    std::vector<std::string> v(2);
    std::string chosen = " -> ";
    std::string nchosen = "    ";
    while (true)
    {
        std::cout << "choose which way to type in:\n";
        std::cout << "1.screen\n";
        for (int i = 0; i < v.size(); ++i)
        {
            if (i == choose)
                std::cout << chosen;
            else
                std::cout << nchosen;
            std::cout << v[i];
        }

    }
    */
    int choose;
    std::string cmd;
loop:
    std::cout << "choose which way to type in:\n";
    std::cout << "1.From file\n";
    std::cout << "2.From keyboard\n";
    std::cin >> choose;
    if (choose == 1)
    {
        if (readFromFile() == 1)
            goto loop;
    }
    else if (choose == 2)
    {
        if (readFromKey() == 1)
            goto loop;
    }
    else if (std::cin >> cmd && cmd == "/back")
    {
        return 0;
    }
loop2:
    std::cout << "choose where to save:\n";
    std::cout << "1.new file\n";
    std::cout << "2.old file\n";

    std::cin >> choose;
    if (choose == 1)
    {
        if (saveToNew() == 1)
            goto loop2;
    }
    else if (choose == 2)
    {
        if (saveToExist() == 1)
            goto loop2;
    }
    else
    {
        std::cin >> cmd;
        if (cmd == "back")
            goto loop;
    }
    return 0;
}

// 读取int失败后清空缓冲区
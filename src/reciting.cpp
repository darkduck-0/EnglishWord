#include "reciting.h"

sign reciting::init()
{

#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    words.reserve(1024);
    Old.reserve(1024);
    New.reserve(1024);
    chis.reserve(1024);
    qus.resize(qusNum);

    if (words.empty())
    {
        cout << "\033[31mThe file is empty.\033[0m\n";
        return UERR;
    }

    if (words.size() < qusNum)
    {
        cout << "\033[31mToo few words.\033[0m\n";
        return UERR;
    }

    for (auto &i : words)
    {
        chis.push_back(&(i.chi));
        if (i.lastTime)
            Old.push_back(&i);
        else
            New.push_back(&i);
    }

    std::reverse(New.begin(), New.end());
    while (Old.size() < qusNum)
    {
        Old.push_back(New.back());
        New.pop_back();
        Old.front()->initTime();
    }
    
    std::make_heap(Old.begin(), Old.end(), compare);
    return FINI;
}
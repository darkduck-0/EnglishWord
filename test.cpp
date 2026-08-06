#include <ctime>
#include <iostream>

int main()
{
    uint64_t now = time(0);
    std::cout << now << std::endl;
    std::cout << "please wait for 15 seconds...\n";
    if (getchar())
    {
        now = time(0);
        std::cout << now << std::endl;
    }
}
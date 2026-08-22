#include <iostream>

using std::cout;

int main()
{
    cout << "\033[36mHello world!\n";
    cout << "\033[?25l";
    getchar();
    getchar();
}
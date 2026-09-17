#include <iostream>
#include <thread>
#include <atomic>

#define WIDTH 32
#define COUNT 64

using std::atomic;
using std::cout, std::flush;

atomic<bool> timeout;
extern atomic<bool> answered;
extern atomic<bool> activate;
extern const float timeLim;

int countDown(float t)
{
    uint32_t dt;
    dt = (uint32_t)(t * 1000 / COUNT);
    for (int i = 0; i <= COUNT; ++i)
    {
        if (answered)
            return 0;
        cout << "\r\033[2K";

        cout << "[\033[42m";
        int length = i * WIDTH / COUNT;
        length = WIDTH - length;
        for (int j = 0; j < length; ++j)
            cout << ' ';

        cout << "\033[0m";
        for (int j = length; j < WIDTH; ++j)
            cout << ' ';

        int sec = length * (int)t / WIDTH;
        cout << ']' << ' ' << sec << " s" << flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(dt));
    }
    timeout = true;
    cout << "\n\033[31mTime out.\033[0m" << std::endl;
    return 1;
}

void fun1()
{
    for (;;)
    {
        if (activate)
        {
            cout << "\033[9H";
            countDown(timeLim);
        }
    }
}
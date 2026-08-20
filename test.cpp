#include <iostream>
#include <thread>
#include <chrono>

void progressBar(int percent)
{
    std::cout << "\r\033[2K";  // 回到行首并清除整行
    std::cout << "\033[1;36m"; // 粗体+青色

    int barWidth = 50;
    int progress = (percent * barWidth) / 100;

    std::cout << "[";
    for (int i = 0; i < barWidth; ++i)
    {
        if (i < progress)
        {
            std::cout << "\033[42m \033[0m\033[1;36m"; // 绿色块
        }
        else
        {
            std::cout << " ";
        }
    }
    std::cout << "] " << percent << "%\033[0m";
    std::cout.flush();
}

int main()
{
    std::cout << "\033[?25l";           // 隐藏光标
    std::cout << "\033]0;进度演示\007"; // 设置标题
    /*
    for (int i = 0; i <= 100; ++i) {
        progressBar(i);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    */
    std::cout << "\n\033[32ma\033[31ma\033[34ma\033[36ma";
    std::cout << "\n\033[?25h"; // 恢复光标
    return 0;
}
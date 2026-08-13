#include <iostream>
#include <string>
#include <map>
#include <functional>
using namespace std;

// 判断是否为数字
bool isNumber(const string& s) {
    if (s.empty()) return false;
    size_t i = 0;
    if (s[0] == '-' || s[0] == '+') {
        if (s.length() == 1) return false;
        i = 1;
    }
    for (; i < s.length(); i++) {
        if (!isdigit(s[i])) return false;
    }
    return true;
}

int main() {
    // 命令映射表
    map<string, function<void()>> commands;
    
    commands["help"] = []() {
        cout << "可用命令: help, quit, info, clear" << endl;
    };
    
    commands["quit"] = []() {
        cout << "退出程序" << endl;
        exit(0);
    };
    
    commands["info"] = []() {
        cout << "数字/命令混合处理器 v1.0" << endl;
    };
    
    commands["clear"] = []() {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    };
    
    string input;
    
    while (true) {
        cout << "> ";
        cin >> input;
        
        if (isNumber(input)) {
            int num = stoi(input);
            cout << "收到数字: " << num << " (平方: " << num * num << ")" << endl;
        }
        else if (commands.find(input) != commands.end()) {
            commands[input]();  // 执行命令
        }
        else {
            cout << "未知输入: " << input << "，输入 help 查看帮助" << endl;
        }
    }
    
    return 0;
}
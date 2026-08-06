#include "word.cpp"
#include <vector>
#include <string>

std::vector<Word> v;
int main()
{
    std::string a = "hello", b = "你好";
    Word n(a, b);
    v.push_back(n);
}
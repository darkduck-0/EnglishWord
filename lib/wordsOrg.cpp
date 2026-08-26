#include "wordsOrg.h"
#include <vector>
#include <string>
#include "word.h"
#include <algorithm>
#include "sign.h"
#include <chrono>

using std::cout, std::cin, std::endl;
using std::vector, std::string;
using std::make_heap, std::pop_heap, std::push_heap;


void initWords()
{
    waiting.reserve(1024);
    ready.reserve(1024);
    make_heap(waiting.begin(), waiting.end(), compare);
    waitingMove();
    make_heap(ready.begin(), ready.end(), compare);
}


static void moveWord(vector<Word *> &a, vector<Word *> &b)
{
    b.push_back(a.front());
    push_heap(b.begin(), b.end(), compare);
    pop_heap(a.begin(), a.end(), compare);
    a.pop_back();
}


void readyMove()
{
    uint64_t now = time(0);
    if (ready.front()->nextTime > now)
        moveWord(ready, waiting);
    else
    {
        pop_heap(ready.begin(), ready.end(), compare);
        push_heap(ready.begin(), ready.end(), compare);
    }
}


void waitingMove()
{
    uint64_t now = time(0);
    while (waiting.front()->nextTime > now)
        moveWord(waiting, ready);
}
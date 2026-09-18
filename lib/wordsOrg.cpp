#include "wordsOrg.h"
#include "word.h"
#include "sign.h"
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>

static auto compare = [](Word *x, Word *y)
{ return *x > *y; };

using std::cout, std::cin, std::endl;
using std::make_heap, std::pop_heap, std::push_heap;
using std::vector, std::string;

static vector<Word *> waiting, newWords;
vector<Word *> ready;

void showProcess()
{
    extern vector<Word> words;
    cout << "Total: " << words.size() << "\t";
    cout << "Ready: " << ready.size() << "\t";
    cout << "New: " << newWords.size() << endl;
}

void initOrg()
{
    extern vector<Word> words;
    waiting.reserve(1024);
    ready.reserve(1024);
    newWords.reserve(1024);

    for (auto &i : words)
    {
        if (i.isNew())
            newWords.push_back(&i);
        else if (i.timeUp())
            ready.push_back(&i);
        else
            waiting.push_back(&i);
    }

    make_heap(waiting.begin(), waiting.end(), compare);
    make_heap(ready.begin(), ready.end(), compare);
    std::reverse(newWords.begin(), newWords.end());
}

static void moveWord(vector<Word *> &a, vector<Word *> &b)
{
    b.push_back(a.front());
    push_heap(b.begin(), b.end(), compare);
    pop_heap(a.begin(), a.end(), compare);
    a.pop_back();
}

static void readyMove()
{
    if (ready.empty())
        return;
    if (!ready.front()->timeUp())
        moveWord(ready, waiting);
    else
    {
        pop_heap(ready.begin(), ready.end(), compare);
        push_heap(ready.begin(), ready.end(), compare);
    }
}

static void waitingMove()
{
    while (!waiting.empty() && waiting.front()->timeUp())
        moveWord(waiting, ready);
}

int maintain()
{
    readyMove();
    waitingMove();
    return ready.size();
}
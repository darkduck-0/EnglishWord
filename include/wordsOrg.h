#ifndef WORDSORG
#define WORDSORG


static auto compare = [](Word *x, Word *y)
{ return *x > *y; };


void initWords();
void readyMove();
void waitingMove();


extern vector<Word *> waiting, ready;


#endif
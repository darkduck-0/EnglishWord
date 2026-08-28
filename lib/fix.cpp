#include <vector>
#include "word.h"
using std::vector;
vector<Word> words;
vector<Word *> waiting, ready, newWords;  // From start
size_t optSize;
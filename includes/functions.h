//#ifndef __FUNCTIONS_H__
//#define __FUNCTIONS_H__

//#include <string>
//#include <vector>
//#include <utility>
//#include "../classes/Lexicon.h"
//#include "../classes/PairCount.h"
//#include "../classes/SingleCount.h"

using namespace std;

vector<string> stringSplit(string str, string delim);
vector<unsigned int> insertAndConvert2intVector(string line, Lexicon& lex, SingleCount& sinlgesObject);
void showFreq(PairCount& pairs, SingleCount& singlesF, SingleCount& singlesE, Lexicon& f, Lexicon& e);

//#endif


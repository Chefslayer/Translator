#include <iostream>
#include <utility>
#include <math.h>
#include "output.h"
#include "../classes/SingleCount.h"
#include "../classes/PairCount.h"
#include "../classes/Lexicon.h"

using namespace std;

void showFreq( PairCount& pairs, SingleCount& singlesF, SingleCount& singlesE, Lexicon& f, Lexicon& e)
{
	for (pairs.begin(); !pairs.isEnd(); pairs.next())
	{
	pair<unsigned int, unsigned int> wordpair = pairs.current();
	double relFreq_f = -log(((double)pairs.getFreq(wordpair))/((double)singlesF.getFreq(wordpair.first)));
	double relFreq_e = -log(((double)pairs.getFreq(wordpair))/((double)singlesE.getFreq(wordpair.second)));
	cout << relFreq_f << " " << relFreq_e << " # " << f.getWord(wordpair.first) << " # " << e.getWord(wordpair.second) << endl;
 	}
}

void showFreqPhrases()
{
	// TODO
}

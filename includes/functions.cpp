#include <string>
#include <vector>
#include <utility>
#include <iostream>
#include <sstream>
#include <math.h>
#include "functions.h"
#include "../classes/Lexicon.h"
#include "../classes/PairCount.h"
#include "../classes/SingleCount.h"

using namespace std;

/**
* splits a string into tokens
*
* \param str the string to split
* \param delim delim[0] is used as delimiter
* \return a vector with all tokens
*/
vector<string> stringSplit(string str, string delim)
{
	vector<string> result;
	istringstream iss(str);
	string token;
	while (getline(iss, token, delim[0]))
	{
		result.push_back(token);
	}
	return result;
}

/**
* displays the Freqs on the cout
*
* \param pairs the pairs-object
* \param singlesF singles-object for source lang
* \param singlesE singles-object for target lang
* \param f lexicon to look up the words of the source lang
* \param e lexicon to look up the words of the target lang
*/
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

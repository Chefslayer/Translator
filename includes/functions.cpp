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

/*	gets a line, lexicon and singleCount object puts all words of the sentence in the lexicon and saves the word-values in the singlesObject
	
	@param line				a sentence
	@param lex				the lexicon
	@param singlesObject	the SingleCount Object to count the singles
	@return					a vector with the sentence in values
*/
vector<unsigned int> insertAndConvert2intVector(string line, Lexicon& lex, SingleCount& sinlgesObject)
{
	vector<string>words = stringSplit(line, " ");
			
	vector<unsigned int> result(words.size(), 0);
	
	//put all words of the sentence in source language-lexicon and the value of the word into the lang-object
	unsigned int i;
	for (i=0; i<words.size(); i++)
	{
		unsigned int val = lex.insert(words[i]);
		sinlgesObject.insert(val);
		result[i] = val;
	}
	return result;
}

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

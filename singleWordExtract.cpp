#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <utility>
#include <math.h>
#include "constants.h"
#include "gzstream.h"
#include "Lexicon.h"
#include "SingleCount.h"
#include "PairCount.h"
#include "functions.h"

using namespace std;

static Lexicon f("italienisch");
static Lexicon e("englisch");

int main(int argc, char* argv[])
{
	vector<string> source;
	vector<string> destination;
	vector<unsigned int> srcWords;
	vector<unsigned int> destWords;
	vector<pair<string,string> > wordPairs;
	pair<unsigned int, unsigned int> temp;
	string line, word, srcWord, destWord;
	unsigned int i = 0, sentenceNum, srcWordNum, destWordNum;
	
	// variables hold all data
	SingleCount singlesF;
	SingleCount singlesE;
	PairCount pairs;
	
	// open files
	ifstream src(argv[1]);
	ifstream dest(argv[2]);
	igzstream alig(argv[3]);
	if (!(src.good() && dest.good() && alig.good()))
	{
		cerr << "ERROR: Opening file failed.\n";
		return 0; // EXIT_FAILURE;
	}
	
	// read files

	//alignment
	while(alig >> word)
	{
		if (word == "SENT:")
		{
			//put all words of the sentence in source language-lexicon and the value of the word into the lang-object
			getline(src,line);
			srcWords = insertAndConvert2intVector(line, f, singlesF);
	
			getline(dest,line);
			destWords = insertAndConvert2intVector(line, e, singlesE);

			//alig >> sentenceNum;
			//..
			//cout << "in Satz " << sentenceNum << " sind folgende Wortpaare einander zugeordnet:"<< endl;
		}
		else if (word == "S")
		{
			alig >> srcWordNum;
			alig >> destWordNum;
			if (srcWords.size() <= srcWordNum || destWords.size() <= destWordNum)
			{
				cout << "Fehler: In der Quell- oder Zielsprache sind zuwenig Wörter" << endl;
			}
			else
			{
				temp = pair<unsigned int, unsigned int>(srcWords[srcWordNum], destWords[destWordNum]);
				// save the src-target pair
				pairs.insert(temp);
			}
		}
	}
	
	//output
	showFreq(pairs, singlesF, singlesE, f, e);
	return 0; //EXIT_SUCCESS;
}

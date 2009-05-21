#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <utility>
#include <math.h>
#include "includes/constants.h"
#include "lib/gzstream.h"
#include "classes/Lexicon.h"
#include "classes/SingleCount.h"
#include "classes/PairCount.h"
#include "includes/functions.h"

using namespace std;

static Lexicon f;
static Lexicon e;

int main(int argc, char* argv[])
{
	if (argc < 4)
	{
		cerr << "ERROR: not enough parameters" << endl << "Usage: " << argv[0] << " source-doc target-doc alignment" << endl;
		return 0; // EXIT_FAILURE;
	}

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

	if (!src.good())
	{
		cerr << "ERROR: Opening source-language ("<< argv[1] <<") failed." << endl;
		return 0; // EXIT_FAILURE;
	}

	if (!dest.good())
	{
		cerr << "ERROR: Opening target-language ("<< argv[2] <<") failed." << endl;
		return 0; // EXIT_FAILURE;
	}

	if (!alig.good())
	{
		cerr << "ERROR: Opening alignment ("<< argv[3] <<") failed."  << endl;
		return 0; // EXIT_FAILURE;
	}

	//alignment
	while(alig >> word)
	{
		if (word == "SENT:")
		{
			//put all words of the sentence in source language-lexicon and the value of the word into the lang-object
			getline(src,line);
			srcWords = f.insertSentence(line, &singlesF);

			getline(dest,line);
			destWords = e.insertSentence(line, &singlesE);

			alig >> sentenceNum;
			
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

/**
 * @file
 * @author  Gruppe 2
 * @version 1.0
 *
 * @section DESCRIPTION
 *
 * This program calculates a translation table, which is used during a translation to find the best hypothesis.
 * It expects 3 parameters: a <b>source-doc</b>, a <b>target-doc</b> and the <b>alignment</b>.
 * It outputs the translation-table in this format line by line:
 * 		<double> relFreq_f <double> relFreq_e # <string> fWord # <string> eWord
 */

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
#include "includes/output.h"

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

	vector<unsigned int> srcWords;
	vector<unsigned int> destWords;
	string srcLine, destLine word;
	
	// variables hold all data
	Tree phrasesF;
	Tree phrasesE;
	Tree phrasepairs;
	
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

	Alignment* aligObj = new Alignment(alig, f, e);

	// get src and dest lines
	while (getline(src,srcLine) && getline(dest,destLine))
	{
		//put all words of the sentence in source language-lexicon and the value of the word into the lang-object
		srcWords = f.insertSentence(srcLine, &singlesF);
		destWords = e.insertSentence(destLine, &singlesE);

		// init the alignment for these sentences
		aligObj->nextSentence(srcLine.size(), destLine.size());

		// get phrases
		unsigned int i1=i2=0;
		for (unsigned int j1 = 0; j1<src.length(); j1++)
		{
			for (unsigned int j2 = i1; j2<src.length(); j2++)
			{
				i1 = aligObj->getMinTargetAlig(j1, j2);
				i2 = aligObj->getMaxTargetAlig(j1, j2);
				if (aligObj->getMinSrcAlig(i1, i2) == j1 && aligObj->getMaxSrcAlig(i1, i2) == j2)
				{
					/* TODO: output in alle 3 trees einfügen.
					 * 1. tree = phrasesF - src-lang phrasen count (präfixbaum)
					 * 2. tree = phrasesE - target-lang phrasen count (präfixbaum)
					 * 3. tree = phrasepairs - phrasenpaare count (präfixbaum von präfixbäumen)
					 */
					aligObj->outputPhrase(j1, j2, i1, i2)
				}
			}
		}
	}
	// TODO output
	return 0; //EXIT_SUCCESS;
}

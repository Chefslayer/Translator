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
#include "classes/Tree.h"
#include "classes/TreeOfTrees.h"
#include "classes/Alignment.h"
#include "includes/PhrasePair.h"
#include "includes/output.h"

using namespace std;

static Lexicon f;
static Lexicon e;

int main(int argc, char** argv)
{
	if (argc < 4)
	{
		cerr << "ERROR: not enough parameters" << endl << "Usage: " << argv[0] << " source-doc target-doc alignment" << endl;
		return 0; // EXIT_FAILURE;
	}

	// open files
	ifstream src(argv[1]);
	ifstream dest(argv[2]);

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

	// variables holding all data

	/// holds the Alignment and finds all valid phrases etc..
	Alignment* aligObj;
	try
	{
		aligObj = new Alignment(argv[3]);
	}
	catch (bool openFileFail)
	{
		cerr << "ERROR: Opening alignment ("<< argv[3] <<") failed."  << endl;
		return 0; // EXIT_FAILURE;
	}

	/// src-lang phrase count (prefixtree of words) - initialized with the 0-word as root
	Tree *phrasesF = new Tree(new Node(0));

	/// target-lang phrase count (prefixtree of words) - initialized with the 0-word as root
	Tree *phrasesE = new Tree(new Node(0));

	/// phrasepair count (prefixtree of prefixtrees) - initialized with a Tree as root which is initialized with the 0-word as root
	TreeOfTrees* phrasePairs = new TreeOfTrees(new NodeOfTrees(0, NULL));

	vector<unsigned int> srcWords;
	vector<unsigned int> destWords;
	string srcLine, destLine;

	unsigned int lineNr = 1;
	// get src and dest lines
	while (getline(src,srcLine) && getline(dest,destLine))
	{

		//put all words of the sentence in source language-lexicon and the value of the word into the lang-object
		srcWords = f.insertSentence(srcLine);
		destWords = e.insertSentence(destLine);

		// init the alignment for these sentences
		aligObj->nextSentence(srcLine.size(), destLine.size());

		// get phrases
		unsigned int i1=0,i2=0;
		for (unsigned int j1 = 0; j1<srcLine.size(); j1++)
		{
			for (unsigned int j2 = i1; j2<srcLine.size(); j2++)
			{
				i1 = aligObj->getMinTargetAlig(j1, j2);
				i2 = aligObj->getMaxTargetAlig(j1, j2);
				if (aligObj->getMinSrcAlig(i1, i2) == j1 && aligObj->getMaxSrcAlig(i1, i2) == j2)
				{
					PhrasePair* p = aligObj->outputPhrase(j1, j2, i1, i2, srcWords, destWords);

					// put phrase in source-lang-obj
					phrasesF->insert(p->src);

					// put phrase in target-lang-obj
					phrasesE->insert(p->target);

					// count phrasePair
					phrasePairs->insert(p);
				}
			}
		}

		if (lineNr/100==(double)lineNr/(double)100) 
		cout<< "line" << lineNr <<endl;
		if (lineNr>TRAINING_LINES) break;
		lineNr++;
	}	 

	showFreqPhrases(phrasePairs, phrasesF, phrasesE, f, e);

	return 0; //EXIT_SUCCESS;
}

/**
 * @file
 * @author  Gruppe 2
 * @version 1.0
 *
 * @section DESCRIPTION
 *
 * This program translates a source-document line by line.
 * It expects 2 parameters: a <b>translation-table</b> and the <b>source-document</b> which is going to be translated.
 * Output is the guessed translation line by line.
 */

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <utility>
#include <math.h>
#include <stack>
#include <algorithm>
#include "includes/constants.h"
#include "includes/hypothesis.h"
#include "includes/functions.h"
#include "includes/output.h"
#include <Vocab.h>
#include <Ngram.h>

using namespace std;

//static Vocab vocab;
static Vocab e;
static Ngram* ngram;

int main(int argc, char* argv[])
{
	if (argc < 3)
	{
		cerr << "ERROR: not enough parameters" << endl << "Usage: " << argv[0] << " translated-document language-model" << endl;
		return 0; // EXIT_FAILURE;
	}

	// open files
	ifstream trans_doc(argv[1]);
	if (!trans_doc.good())
	{
		cerr << "ERROR: Opening translated document ("<< argv[1] <<") failed." << endl;
		return 1; // EXIT_FAILURE;
	}
	ngram = new Ngram(e, defaultNgramOrder);
	File f = fopen(argv[2], "r");
	ngram->read(f, false);

	string line;

	while (getline(trans_doc, line))
	{
		double bestScore = numeric_limits<double>::max();
		vector<string>* bestTrans;
		vector<string> currentTrans;

		for (unsigned int transCount=0; transCount < KEEP_N_BEST_HYPOS; transCount++)
		{
	       		// line is formated like: "<double>#<string> ... <string>"
			vector<string> line_vec = stringSplit(line, "#");

			double score;
			istringstream isstrF(line_vec[0]);
			isstrF >> score;

			currentTrans.clear();
			currentTrans = stringSplit(line_vec[1], " ");

			// fill buffer
			VocabIndex* buf = new VocabIndex[currentTrans.size()+3];
	
			buf[0]=e.seIndex();
			for (int i=currentTrans.size()-1; i>=0; i--)
			{
				buf[i+1]= e.addWord(currentTrans[i].c_str());
			}
			buf[currentTrans.size()+1] = e.ssIndex();
			buf[currentTrans.size()+2] = Vocab_None;

			// rate the translation with srilm
			double sriScore = ngram->wordProb(buf[1], &buf[1+1]);
			double currentScore = score + sriScore;

			if (currentScore < bestScore)
			{
				bestScore = currentScore;
				bestTrans = &currentTrans;
			}
			if (transCount < KEEP_N_BEST_HYPOS-1)
				getline(trans_doc, line);
		}
		string bestTranslation = "";
		for (int i=0; i<bestTrans->size(); i++)
		{
			bestTranslation += (bestTranslation==""?"":" ") + (string)(*bestTrans)[i];
		}
		cout << bestTranslation << endl;
	}

	return 0; //EXIT_SUCCESS;
}

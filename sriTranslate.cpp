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

static Vocab f;
static Vocab e;

/*
 * holds information about a phrasepair from a translation-table.
 */
struct trans_phrase_tab_struct
{
	/// relative Frequence of F
	double relFreqF;
	/// relative Frequence of E
	double relFreqE;

	/// word-codes of the source-phrase
	vector<unsigned int> f;
	/// word-codes of the target-phrase
	vector<unsigned int> e;
};



int main(int argc, char* argv[])
{
	if (argc < 3)
	{
		cerr << "ERROR: not enough parameters" << endl << "Usage: " << argv[0] << " translation-table source-document" << endl;
		return 0; // EXIT_FAILURE;
	}

	// open files
	ifstream trans_tab(argv[1]);
	ifstream src_doc(argv[2]);
	if (!trans_tab.good())
	{
		cerr << "ERROR: Opening translation table ("<< argv[1] <<") failed." << endl;
		return 1; // EXIT_FAILURE;
	}
	if (!src_doc.good())
	{
		cerr << "ERROR: Opening source document ("<< argv[2] <<") failed." << endl;
		return 1; // EXIT_FAILURE;
	}

	unsigned int i = 0;
	vector<struct trans_phrase_tab_struct> trans_phrase_tab_vec;
	trans_phrase_tab_vec.resize(VECTOR_INIT_SIZE);
	string line;

	// read trans_tab into trans_phrase_tab_vec
	while (getline(trans_tab, line))
	{
		struct trans_phrase_tab_struct current;
		double temp;
       		// line is formatted like: <double> <double> # <string> ... <string> # <string> ... <string>

		vector<string> line_vec = stringSplit(line, "#");
		// watch out for spaces!
		// line_vec[0] == "<double> <double> "
		// line_vec[1] == " <string> ... <string> "
		// line_vec[2] == " <string> ... <string>"

		vector<string> freqs_vec = stringSplit(line_vec[0], " ");

		istringstream isstrF(freqs_vec[0]);
		isstrF >> temp;
		current.relFreqF = temp;

		istringstream isstrE(freqs_vec[1]);
		isstrE >> temp;
		current.relFreqE = temp;

		vector<string> tempV;

		// insert src phras
		tempV = stringSplit(line_vec[1], " ");
		for (int j = 0; j <= line_vec[1].size(); j++)
			{
				current.f.push_back(f.addWord(tempV[j].c_str()));
			}

		// insert target phrase
		tempV.clear();
		tempV = stringSplit(line_vec[2], " ");
		for (int k = 0; k <= line_vec[2].size(); k++)
			{
				current.e.push_back(e.addWord(tempV[k].c_str()));
			}

		if (i >= trans_phrase_tab_vec.size())
		{
			trans_phrase_tab_vec.resize(trans_phrase_tab_vec.size() + VECTOR_RESIZE);
 		}
		trans_phrase_tab_vec[i] = current;
		// cout << f.getWord(current.f) << " " << current.relFreqF << endl;
		i++;
		if (i/100==(double)i/(double)100)
			cout<< "line" << i <<endl;
//		if (i>TRAINING_LINES) break;
	}
	trans_phrase_tab_vec.resize(i);

	// translate src_doc
	int c = 0;
	/*while (getline(src_doc, line))
	{
		c++;
		if (c > 10) break;
		vector<string> stringwords = stringSplit(line, " ");
		vector<unsigned int> words(stringwords.size(), 0);

		for (unsigned int i = 0; i < stringwords.size(); i++)
		{
			words[i] = f.getNum(stringwords[i]);
		}

		Hypothesis* transHyp = searchTranslation(words, trans_phrase_tab_vec);

		string translation = "";
		while (transHyp->prevHyp != NULL)
		{
			string tmp="";
			for (unsigned int i = 0; i < transHyp->phraseTrans.size(); ++i ){
				tmp += (tmp== ""?"":" ") + e.getWord(transHyp->phraseTrans[i]);
			}
			translation = tmp+" "+translation;

			transHyp = transHyp->prevHyp;
		}
		cout << translation << endl;
	}
	*/

	return 0; //EXIT_SUCCESS;
}

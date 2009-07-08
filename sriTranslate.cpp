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

/**
 * holds information about a translation of a phrase
 */
struct phrase_translation_struct
{
	/// relative Frequence of F
	double relFreqF;
	/// relative Frequence of E
	double relFreqE;
	/// the length of the phrase in f
	unsigned int phraseLength;
	/// word-codes of the target-phrase
	vector<unsigned int> e;
};

/** Prunes the Stack to KEEP_N_BEST_HYPOS elements.
 *
 *   \param s reference to stack of hypthesis
 *   \return reference to best Hypothesis in s
 */
Hypothesis* pruneStack(stack < Hypothesis* > &s)
{
	vector<Hypothesis*> v;
	unsigned int size = s.size();
	v.resize(size);

	for (unsigned int i=0; !s.empty(); i++)
	{
		v[i] = s.top();
		s.pop();
	}
	sort(v.begin(), v.end(), cmp_Hyp);

	for (unsigned int i=0; i<size && i<KEEP_N_BEST_HYPOS ;i++)
	{
		s.push(v[i]);
	}
	//return best Hypo
	return v[0];
}

/**
 * searches a translation for a given line of text.
 *
 * \param words a vector of words which will be translatet
 * \param translationtab table of translations
 * \return best Hypothesis
 */
Hypothesis* searchTranslation(vector<unsigned int> &words, vector<trans_phrase_tab_struct>  &translationtab)
{
	Hypothesis* minCostsHyp;
	vector< stack < Hypothesis* > > stacks;
	stacks.resize((words.size()+1));
	vector<unsigned int> tmp;
	tmp.push_back(0);
	Hypothesis* h = new Hypothesis(NULL,0,0,tmp);
	stacks[0].push(h);

	for (unsigned int stackNr = 0; stackNr < stacks.size()-1; stackNr++)
	{
//		cout << stackNr << endl;
		vector<phrase_translation_struct> phrases;
		phrases.clear();

		bool found_at_least_one_hypo = false;

		for (unsigned int phraseLength = 1; phraseLength <= MAX_PHRASE_LENGTH && stackNr+phraseLength<words.size(); phraseLength++)
		{
			vector<unsigned int> phraseF;
			phraseF.clear();
			for (unsigned int k = 0; k < phraseLength; k++)
			{
				phraseF.push_back(words[stackNr+k]);
			}
			// search for all possible translations and save it for later to create the hypos

			// search for first occurance of phraseF in transtab
			unsigned int transTabPos = 0;
			while (transTabPos < translationtab.size() && phraseF != translationtab[transTabPos].f)
			{
				transTabPos++;
			}
			// search for all following occurances of phraseF in transtab
			while (transTabPos < translationtab.size() && phraseF == translationtab[transTabPos].f)
			{
				found_at_least_one_hypo = true;
				phrase_translation_struct currentTranslation;

				currentTranslation.relFreqF = translationtab[transTabPos].relFreqF; 
				currentTranslation.relFreqE = translationtab[transTabPos].relFreqE;
				currentTranslation.phraseLength = phraseLength;
				currentTranslation.e = translationtab[transTabPos].e;

				phrases.push_back(currentTranslation);
				transTabPos++;
			}
		}
		if (!found_at_least_one_hypo)
		{
			// insert '?'
			phrase_translation_struct currentTranslation;

			currentTranslation.relFreqF = 20;
			currentTranslation.relFreqE = 20;
			currentTranslation.phraseLength = 1;
			vector<unsigned int> tmp(0);
			currentTranslation.e = tmp;

			phrases.push_back(currentTranslation);
		}

		// create for each hypo in the current stack the new hypos of the current phrases
		while (!stacks[stackNr].empty())
		{
			Hypothesis *prev = stacks[stackNr].top();

			for (vector<phrase_translation_struct>::iterator it = phrases.begin(); it != phrases.end(); it++)
			{
				Hypothesis *h = new Hypothesis(prev, it->relFreqF, it->relFreqE, it->e);
				stacks[ stackNr + it->phraseLength ].push(h);
			}
			stacks[stackNr].pop();
		}
		minCostsHyp = pruneStack(stacks[stackNr+1]);
	}

	// return best Hypothesis of the last stack
	return minCostsHyp;
}

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
/*		VocabIndex *vocabBuffer(new VocabIndex[50]); -> brauchen wir doch noch gar nicht?!
		// wofür wird das gebraucht und wie ist die syntax? -> ssIndex = <s>
		VocabIndex ssIndex();
		// wofür wird das gebraucht und wie ist die syntax? -> seIndex = </s>
		VocabIndex seIndex();
*/
		// insert src phrase
		tempV.clear();
		tempV = stringSplit(line_vec[1], " ");
		tempV.erase(tempV.begin());
		tempV.pop_back();

		for (int j = tempV.size()-1; j >= 0; j--)
		{
			current.f.push_back(f.addWord(tempV[j].c_str()));
		}

		// insert target phrase
		tempV.clear();
		tempV = stringSplit(line_vec[2], " ");
		tempV.erase(tempV.begin());

		for (int k = tempV.size()-1; k >= 0; k--)
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
	while (getline(src_doc, line))
	{
		c++;
		if (c > 10) break;
		vector<string> stringwords = stringSplit(line, " ");
		vector<VocabIndex> words(stringwords.size(), 0);

		for (unsigned int i = 0; i < stringwords.size(); i++)
		{
			words[i] = f.addWord(stringwords[i].c_str());
		}

		Hypothesis* transHyp = searchTranslation(words, trans_phrase_tab_vec);

		string translation = "";
		while (transHyp->prevHyp != NULL)
		{
			string tmp="";
			for (unsigned int i = 0; i < transHyp->phraseTrans.size(); ++i ){
			//	tmp += (tmp== ""?"":" ") + vocab.addWord((transHyp->phraseTrans[i]).c_str());
				tmp += (tmp== ""?"":" ") + (string)e.getWord(transHyp->phraseTrans[i]);
			}
			translation = tmp+" "+translation;

			transHyp = transHyp->prevHyp;
		}
		cout << translation << endl;
	}

	return 0; //EXIT_SUCCESS;
}

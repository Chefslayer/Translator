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
#include "classes/Lexicon.h"
#include "includes/hypothesis.h"
#include "includes/functions.h"
#include "includes/output.h"

using namespace std;

static Lexicon f;
static Lexicon e;

/**
 * holds information about a wordpair from a translation-table.
 */
struct trans_phrase_tab_struct
{
	/// relative Frequence of F
	double	relFreqF,
	/// relative Frequence of E
		relFreqE;

	/// word-codes of the source-word
	vector<unsigned int>	f,
	/// word-codes of the target-word
			e;
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


	for (unsigned int i = 0; i < words.size()-2; i++)
	{
		for (unsigned int j = 0; j < 3; j++){
			vector<unsigned int> phraseF;
			for (unsigned int k = 0; k < j+1; ++k){
				phraseF.push_back(words[i+k]);
			}
		unsigned int pos = 0;
		// find first occurance of word[i] in transtab
		while (j < translationtab.size() && phraseF != (translationtab[j].f))
		{
			j++;
		}
		unsigned int first_occ = pos;

		while (!stacks[i].empty())
		{
			Hypothesis *prev = stacks[i+j].top();

			// make hyps for all the possible translations
			j = first_occ;
			bool found_at_least_one_hypo = false;
			while (j < translationtab.size() && phraseF == (translationtab[pos].f))
			{
				found_at_least_one_hypo = true;
				Hypothesis *h = new Hypothesis(prev, translationtab[pos].relFreqF, translationtab[pos].relFreqE, translationtab[pos].e);
				stacks[i+j+1].push(h);
				pos++;
			}
			if (!found_at_least_one_hypo)
			{
				// insert '(?)'
				vector<unsigned int> tmp;
				tmp.push_back(0);
				
				stacks[i+1].push(new Hypothesis(prev,0, 0, tmp));
			}
			stacks[i].pop();
		}
		minCostsHyp = pruneStack(stacks[i+1]);
	}
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
       
		//TODO get data from line and store in current

		if (i >= trans_phrase_tab_vec.size())
		{
			trans_phrase_tab_vec.resize(trans_phrase_tab_vec.size() + VECTOR_RESIZE);
 		}
		trans_phrase_tab_vec[i] = current;
		// cout << f.getWord(current.f) << " " << current.relFreqF << endl;
		i++;
	}
	trans_phrase_tab_vec.resize(i);

	// translate src_doc
	while (getline(src_doc, line))
	{
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
			for (unsigned int i = 0; i < transHyp->phraseTrans.size(); ++i ){
				translation = e.getWord(transHyp->phraseTrans[i]) + " " + translation;
			}
			transHyp = transHyp->prevHyp;
		}
		cout << translation << endl;
	}

	return 0; //EXIT_SUCCESS;
}

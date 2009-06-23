#include <iostream>
#include <utility>
#include <math.h>
#include "output.h"
#include "../classes/SingleCount.h"
#include "../classes/PairCount.h"
#include "../classes/Lexicon.h"
#include "../classes/Tree.h"
#include "../classes/TreeOfTrees.h"

using namespace std;

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

/*
void showFreqPhrases_subTrees_rek(Node<unsigned int> *current, const string &s_f, string s_e, vector<unsigned int> v_f, vector<unsigned int> v_e, Tree<unsigned int> *phrasesF, Tree<unsigned int> *phrasesE, Lexicon &e)
{
	//double rel = ...;
	if (current->value != 0)
	{
		double relFreq_f = -log(((double)current->count)/((double)phrasesF->getCount(v_f)));
		double relFreq_e = -log(((double)current->count)/((double)phrasesE->getCount(v_e)));
		s_e += (s_e==""?"":" ") + e.getWord(current->value);
		v_e.push_back(current->value);

		cout << relFreq_f << " " << relFreq_e << " # " << s_f << " # " << s_e << endl;
	}

	for (unsigned int i=0; i<current->childNodes.size(); i++)
	{
		showFreqPhrases_subTrees_rek(current->childNodes[i], s_f, s_e, v_f, v_e, phrasesF, phrasesE, e);
	}
}

void showFreqPhrases_subTrees(string s_f, vector<unsigned int> v_f, Tree<unsigned int> *t, Tree<unsigned int> *phrasesF, Tree<unsigned int> *phrasesE, Lexicon &e)
{
	if ( t!=NULL)
	{
		string s_e = "";
		vector<unsigned int> v_e;
		showFreqPhrases_subTrees_rek(t->getRoot(), s_f, s_e, v_f, v_e, phrasesF, phrasesE, e);
	}
}

void showFreqPhrases_rek(Node<NodeOfTrees*>* current, string s_f, vector<unsigned int> v_f, Tree<unsigned int> *phrasesF, Tree<unsigned int> *phrasesE, Lexicon &f, Lexicon &e)
{
	if (current->value->word != 0)
	{
		s_f += (s_f==""?"":" ") + f.getWord(current->value->word);
		v_f.push_back(current->value->word);
	}

	showFreqPhrases_subTrees(s_f, v_f, current->value->tree, phrasesF, phrasesE, e);

	for (unsigned int i=0; i<current->childNodes.size(); i++)
		showFreqPhrases_rek(current->childNodes[i], s_f, v_f, phrasesF, phrasesE, f, e);

}


void showFreqPhrases(Tree<NodeOfTrees*> *phrasePairs, Tree<unsigned int> *phrasesF, Tree<unsigned int> *phrasesE, Lexicon &f, Lexicon &e)
{
	// p # phraseF # phraseE
	vector<unsigned int> v_f;
	string s_f = "";
	showFreqPhrases_rek(phrasePairs->getRoot(), s_f, v_f, phrasesF, phrasesE, f, e);
}
*/

#include <iostream>
#include <utility>
#include <math.h>
#include "output.h"
#include "../classes/SingleCount.h"
#include "../classes/PairCount.h"
#include "../classes/Lexicon.h"
#include "../classes/Tree.h"
#include "../classes/TreeOfTrees.h"
#include "NodeOfTrees.h"

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

void showFreqPhrases(TreeOfTrees *phrasePairs, Tree *phrasesF, Tree *phrasesE, Lexicon &f, Lexicon &e)
{
	// p # phraseF # phraseE
	vector<unsigned int> v_f;
	string s_f = "";
	showFreqPhrases_rek(phrasePairs->root, s_f, v_f, phrasesF, phrasesE, f, e);
}


void showFreqPhrases_subTrees_rek(Node *current, const string &s_f, string s_e, vector<unsigned int> &v_f, vector<unsigned int> v_e, Tree *phrasesF, Tree *phrasesE, Lexicon &e)
{
	if (current->word != 0) // not a root node
	{
		s_e += (s_e==""?"":" ") + e.getWord(current->word);
		v_e.push_back(current->word);

		// check if we saw the v_e-Phrase at least once
		if (current->count>0)
		{
			double relFreq_f = -log(((double)current->count)/((double)phrasesF->getCount(v_f)));
			double relFreq_e = -log(((double)current->count)/((double)phrasesE->getCount(v_e)));
			// relFreq_e==0 means that we saw the v_e-phrase only if we translated it with the v_f and no other v_f
			cout << relFreq_f << " " << relFreq_e << " # " << s_f << " # " << s_e << endl;
		}
	}
	set<Node*, ptr_comp<Node> >::iterator it;
	for ( it = current->childNodes.begin(); it != current->childNodes.end(); it++ )
	{
		showFreqPhrases_subTrees_rek(*it, s_f, s_e, v_f, v_e, phrasesF, phrasesE, e);
	}
}

void showFreqPhrases_subTrees(string &s_f, vector<unsigned int> &v_f, Tree *t, Tree *phrasesF, Tree *phrasesE, Lexicon &e)
{
	if (t != NULL)
	{
		string s_e = "";
		vector<unsigned int> v_e;
		showFreqPhrases_subTrees_rek(t->root, s_f, s_e, v_f, v_e, phrasesF, phrasesE, e);
	}
}

void showFreqPhrases_rek(NodeOfTrees* current, string s_f, vector<unsigned int> v_f, Tree *phrasesF, Tree *phrasesE, Lexicon &f, Lexicon &e)
{
	if (current->word != 0)
	{
		s_f += (s_f==""?"":" ") + f.getWord(current->word);
		v_f.push_back(current->word);
	}

	if (phrasesF->getCount(v_f)>0) // check if we saw v_f-Phrase at least once - otherwise there won't be a translation for it.
		showFreqPhrases_subTrees(s_f, v_f, current->tree, phrasesF, phrasesE, e);

	set<NodeOfTrees*, ptr_ptr_comp<NodeOfTrees> >::iterator it;
	for( it = current->childNodes.begin(); it != current->childNodes.end(); ++it )
	{		
		showFreqPhrases_rek(*it, s_f, v_f, phrasesF, phrasesE, f, e);
	}
}

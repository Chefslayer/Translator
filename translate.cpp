#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <utility>
#include <math.h>
#include <stack>
#include "includes/constants.h"
#include "lib/gzstream.h"
#include "classes/Lexicon.h"
#include "classes/SingleCount.h"
#include "classes/PairCount.h"
#include "includes/hypothesis.h"
#include "includes/functions.h"

using namespace std;

static Lexicon f("italienisch");
static Lexicon e("englisch");

struct trans_tab_struct{
	double relFreqF, relFreqE;
	unsigned int f,e;
};


void pruneStack(stack < Hypothesis > &s)
{
	vector<Hypothesis> v;
//	v.resize(s.size());

	for (unsigned int i=0; !s.empty(); i++)
	{
//		v[i] = s.top();
		v.push_back(s.top());
		s.pop();
	}

	for (unsigned int i=0; i<3 ;i++)
	{
		Hypothesis min = v[i];
		for (unsigned int j=i+1; j<v.size(); j++)
		{
			if (v[j].costs<min.costs)
			{
				Hypothesis h = min;
				min = v[j];
				v[j] = h;
			}
		}
		s.push(min);
	}
}

Hypothesis searchTranslation(string &line, vector<trans_tab_struct>  &translationtab)
{
	vector<string> stringwords = stringSplit(line, " ");
	vector< stack < Hypothesis > > stacks;
	stacks.resize((stringwords.size()+1));
	stacks[0].push(Hypothesis(NULL,0,0));

	vector<unsigned int> words(stringwords.size(), 0);
	
	for (unsigned int i = 0; i < words.size(); i++)
	{

		words[i] = f.getNum(stringwords[i]);

		unsigned int j = 0;
		// find first occurance of word[i] in transtab
		while (j < translationtab.size() && words[i] != (translationtab[j].f))
		{
			j++;
		}
		unsigned int first_occ = j;

		while (!stacks[i].empty())
		{
			Hypothesis *prev = &(stacks[i].top());

			// make hyps for all the possible translations
			j = first_occ;
			while (j < translationtab.size() && words[i] == (translationtab[j].f))
			{
				Hypothesis h = Hypothesis(prev, translationtab[j].relFreqF, translationtab[j].e);
				h.costs = h.costs + prev->costs;
				stacks[i+1].push(h);
				j++;
			}
			stacks[i].pop();
		}
		pruneStack(stacks[i+1]);
	}
	// find best Hypothesis
	Hypothesis current = stacks[words.size()].top();
	stacks[words.size()].pop();
	while (!stacks[words.size()].empty())
	{		
		if ((stacks[words.size()].top().costs) < (current.costs))
			current = stacks[words.size()].top();
		stacks[words.size()].pop();
	}
	return current;
}

int main(int argc, char* argv[])
{

	if (argc < 3)
	{
		cerr << "ERROR: not enough parameters" << endl << "Usage: " << argv[0] << " translation-table source-document" << endl;
		return 0; // EXIT_FAILURE;
	}

	string line;

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
	vector<struct trans_tab_struct> trans_tab_vec;
	trans_tab_vec.resize(VECTOR_INIT_SIZE);

	vector<string> tokens;

	// read trans_tab into trans_tab_vec
	while (getline(trans_tab, line))
	{
		struct trans_tab_struct current;
		char *pch;
		// line is formatted like: <double> <double> # <string> # <string>

		// strtok isn't the right thing to use here. see manpage (Bugs)
		// we may re-implement stringSplit if we need to make it more efficient
		vector<string> line_vec = stringSplit(line, " ");

		istringstream isstrF(line_vec[0]);
		double temp;
		isstrF >> temp;
		current.relFreqF = temp;

		istringstream isstrE(line_vec[1]);
		isstrE >> temp;
		current.relFreqE = temp;

		current.f = f.insert(line_vec[3]);

		current.e = e.insert(line_vec[5]);

		if (i >= trans_tab_vec.size())
		{
			trans_tab_vec.resize(trans_tab_vec.size() + VECTOR_RESIZE);
		}
		trans_tab_vec[i] = current;
		// cout << f.getWord(current.f) << " " << current.relFreqF << endl;
		i++;
	}
	trans_tab_vec.resize(i);

	// translate src_doc
	while (getline(src_doc, line))
	{
		Hypothesis transHyp = searchTranslation(line, trans_tab_vec);
		string translation = "";//e.getWord(transHyp.trans);
		Hypothesis* p = transHyp.prevHyp;
		while (transHyp.prevHyp != NULL)
		{
			translation = e.getWord(transHyp.trans) + " " + translation;
			transHyp = (*transHyp.prevHyp);
		}
		cout << translation << endl;
	}

	return 0; //EXIT_SUCCESS;
}

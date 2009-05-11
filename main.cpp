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

void createhyp(string &line, vector<trans_tab_struct>  &translationtab)
{
	// statt stacknum koennen wir auch i+1 benutzen
	// (wobei wir die doch auch von 0 zaehlen - also eifnach i verwenden koennen, oder nicht? sonst bitte aendern in i+1)
	// unsigned int stacknum = 1;
	vector<string> stringwords = stringSplit(line, " ");
	vector< stack < Hypothesis > > stacks;
	stacks.resize(stringwords.size());
	vector<unsigned int> words(stringwords.size(), 0);

	for (unsigned int i = 0; i < stringwords.size(); i++)
	{
		words[i] = f.getNum(stringwords[i]);
		//TODO klug suchen -> in der trans_tab sind die eintraege doch geordnet nach dem franzoesischen wort oder?
		//dann koennen wir abbrechen, sobald ein anderes wort im franz. vorkommt, nachdem wir das passende einmal gesehen haben?
		//habs mal implementiert
		bool found_word = false;
		for (unsigned int j = 0; j < translationtab.size(); j++)
		{
			if (words[i] == (translationtab[j].f))
			{
				found_word = true;
				stacks[i].push(Hypothesis(translationtab[j].f));
			}
			else if (found_word = true)
			{
				break;
			}
		}
		// stacknum++;
	}
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
		return 0; // EXIT_FAILURE;
	}
	if (!src_doc.good())
	{
		cerr << "ERROR: Opening source document ("<< argv[2] <<") failed." << endl;
		return 0; // EXIT_FAILURE;
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
	}

	// translate src_doc
	while (getline(src_doc, line))
	{
		string translation;
		createhyp(line, trans_tab_vec);
		//translation = translate(line);
		// find best Hypothesis
		translation = "(not translated yet) " + line;
		cout << translation << endl;
	}

	return 0; //EXIT_SUCCESS;
}

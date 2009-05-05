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
#include "includes/functions.h"

using namespace std;

static Lexicon f("italienisch");
static Lexicon e("englisch");

struct trans_tab_struct{
	double relFreqF, relFreqE;
	unsigned int e,f;
};

int main(int argc, char* argv[])
{
	string line;

	// open files
	ifstream trans_tab(argv[1]);
	ifstream src_doc(argv[2]);
	if (!trans_tab.good())
	{
		cerr << "ERROR: Opening translation table ("<< argv[1] <<") failed.\n";
		return 0; // EXIT_FAILURE;
	}
	if (!src_doc.good())
	{
		cerr << "ERROR: Opening source document ("<< argv[2] <<") failed.\n";
		return 0; // EXIT_FAILURE;
	}

	vector<struct trans_tab_struct> trans_tab_vec;
	vector<string> tokens;

	// read trans_tab into trans_tab_vec
	while (getline(trans_tab, line))
	{
		struct trans_tab_struct current;
		char *pch;
		// line is formatted like: <double> <double> # <string> # <string>

		pch = strtok (line," ");
		current.relFreqF = (double)sprintf("%s",pch);

		pch = strtok (NULL," ");
		current.relFreqE = (double)sprintf("%s",pch);

		pch = strtok (NULL," "); // #

		pch = strtok (NULL," ");
		current.f = f.insert(sprintf("%s",pch));

		pch = strtok (NULL," "); // #

		pch = strtok (NULL," ");
		current.e = e.insert(sprintf("%s",pch));

		trans_tab_vec.push_back(current);
	}

	// translate src_doc
	while (getline(src_doc, line))
	{
		string translation;
		// find best Hypothesis
		translation = "hallo";
		cout << translation << endl;
	}

	return 0; //EXIT_SUCCESS;
}

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
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
		cerr << "ERROR: Opening translation table ("<< argv[1] <<") failed." << endl;
		return 0; // EXIT_FAILURE;
	}
	if (!src_doc.good())
	{
		cerr << "ERROR: Opening source document ("<< argv[2] <<") failed." << endl;
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

		trans_tab_vec.push_back(current);
		// cout << f.getWord(current.f) << " " << current.relFreqF << endl;
	}

	// translate src_doc
	while (getline(src_doc, line))
	{
		string translation;
		// find best Hypothesis
		translation = "(not translated yet) " + line;
		cout << translation << endl;
	}

	return 0; //EXIT_SUCCESS;
}

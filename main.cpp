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
		string str;
		// line is formatted like: <double> <double> # <string> # <string>

		//cons_cast usable cause we'll not change the line (read only)
		pch = strtok (const_cast<char*>(line.c_str())," ");

		//make string and convert into double
		str = sprintf("%s",pch);
		istringstream isstrF(str);
		double temp;
		isstrF >> temp;

		current.relFreqF = temp;

		pch = strtok (NULL," ");
		str = sprintf("%s",pch);
		istringstream isstrE(str);
		isstrE >> temp;
		current.relFreqE = temp;

		pch = strtok (NULL," "); // #

		pch = strtok (NULL," ");
		str = sprintf("%s",pch);
		current.f = f.insert(str);

		pch = strtok (NULL," "); // #

		pch = strtok (NULL," ");
		str = sprintf("%s",pch);
		current.e = e.insert(str);

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

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <math.h>
#include "includes/constants.h"
#include "includes/hypothesis.h"
#include "classes/Bleu.h"
#include "classes/Levenshtein.h"

using namespace std;

int main(int argc, char* argv[])
{
	if (argc < 3)
	{
		cerr << "ERROR: not enough parameters" << endl << "Usage: " << argv[0] << " translation reference" << endl;
		return 0; // EXIT_FAILURE;
	}

	// open files
	ifstream trans(argv[1]);
	ifstream reference(argv[2]);
	if (!trans.good())
	{
		cerr << "ERROR: Opening translation ("<< argv[1] <<") failed." << endl;
		return 1; // EXIT_FAILURE;
	}
	if (!reference.good())
	{
		cerr << "ERROR: Opening reference ("<< argv[2] <<") failed." << endl;
		return 1; // EXIT_FAILURE;
	}

	string	trans_line,
		reference_line = "";
	double	average_levenshtein_dist,
		average_posindependent_levenshtein_dist = 0;

	// read trans and reference into trans_vec
	while (getline(trans, trans_line) && getline(reference, reference_line))
	{
		Bleu *current = new Bleu(trans_line, reference_line);
		// cout << current->bla() << endl;
	}

	return 0; //EXIT_SUCCESS;
}

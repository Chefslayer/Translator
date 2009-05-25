/**
 * @file
 * @author  Gruppe 2
 * @version 1.0
 *
 * @section DESCRIPTION
 *
 * This program rates a translation with the BLEU-Score and the Levenshtein-Distance.
 * It expects 2 parameters: a <b>translation</b> and its <b>reference</b>.
 */

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "includes/constants.h"
#include "classes/Lexicon.h"
#include "classes/Bleu.h"
#include "classes/Levenshtein.h"

using namespace std;

static Lexicon l;

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

	string trans_line,
		reference_line = "";
	double average_levenshtein_dist,
		average_posindependent_levenshtein_dist = 0;

	// read trans and reference into trans_vec
	unsigned int sentenceCount = 0;
	Levenshtein *sentence50_lev;
	string sentence50_trans, sentence50_ref;

	while (getline(trans, trans_line) && getline(reference, reference_line))
	{
		vector<unsigned int> current_trans = l.insertSentence(trans_line);
		vector<unsigned int> current_ref = l.insertSentence(reference_line);

		Bleu *current_bleu	 = new Bleu(current_trans, current_ref);
		Levenshtein *current_lev = new Levenshtein(current_trans, current_ref);

		cout << "\n***\nBLEU-Score:\t" << current_bleu->bleuScore(MAX_N_GRAMS) << "\nLevenshtein:\t" << current_lev->getDistance() << "\n\t t: " << trans_line << "\n\t r: " << reference_line << endl;

		sentenceCount++;

		if (sentenceCount==50)
		{
			sentence50_lev = current_lev;
			sentence50_trans = trans_line;
			sentence50_ref = reference_line;
		}
	}

	cout << "\n***\n\n***\nSentence50:\nLevenshtein:\t\t" << sentence50_lev->getDistance()
			  << "\nLevenshtein-Path:\t" << sentence50_lev->getPath() << "\n\t t: " << sentence50_trans << "\n\t r: " << sentence50_ref << endl;

	return 0; //EXIT_SUCCESS;
}

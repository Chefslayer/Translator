#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <math.h>
#include "includes/constants.h"
#include "includes/hypothesis.h"

using namespace std;

struct trans_struct {
	string trans,target;
	double BLEU_score;
};


/**
* calcs the levenshtein distance
*
* \param &trans		translation by machine
* \param &target	translation by human
* \return 
*/
unsigned int levenshtein_distance(string &trans, string &target)
{
	// TODO
	return 0;
}

int main(int argc, char* argv[])
{

	if (argc < 3)
	{
		cerr << "ERROR: not enough parameters" << endl << "Usage: " << argv[0] << " translation target_translation" << endl;
		return 0; // EXIT_FAILURE;
	}

	// open files
	ifstream trans(argv[1]);
	ifstream target(argv[2]);
	if (!trans.good())
	{
		cerr << "ERROR: Opening translation ("<< argv[1] <<") failed." << endl;
		return 1; // EXIT_FAILURE;
	}
	if (!target.good())
	{
		cerr << "ERROR: Opening target_translation ("<< argv[2] <<") failed." << endl;
		return 1; // EXIT_FAILURE;
	}

	unsigned int i = 0;
	string	trans_line,
		target_line = "";
	double	average_levenshtein_dist,
		average_posindependent_levenshtein_dist = 0;
	vector<struct trans_struct> trans_vec;
	trans_vec.resize(VECTOR_INIT_SIZE);

	// read trans and target into trans_vec
	while (getline(trans, trans_line) && getline(trans, target_line))
	{
		struct trans_struct current;
		current.trans = trans_line;
		current.target = target_line;
		// TODO Hypothesen aufstellen?
		current.BLEU_score = 0;
		if (i >= trans_vec.size())
		{
			trans_vec.resize(trans_vec.size() + VECTOR_RESIZE);
		}
		trans_vec[i] = current;
		i++;
	}
	trans_vec.resize(i);

	return 0; //EXIT_SUCCESS;
}

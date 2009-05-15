#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include "includes/constants.h"
#include "includes/hypothesis.h"

using namespace std;

struct trans_struct {
	string trans,target;
	double rate;
};


/**
* calcs the levensthein distance
*
* \param &trans		translation by machine
* \param &target	translation by human
* \return 
*/
unsigned int levensthein_distance(string &trans, string &target)
{
	// TODO
	return 0;
}

/**
*
*
* \param n
* \param H reference to the Hypothesis to count the n-grams for
* \return 
*/
unsigned int count_n_grams(unsigned int n, Hypothesis* H)
{
	// TODO
	return 0;
}

/**
* calcs the precision of a Hypothesis
*
* \param C reference to the Hypothesis to calc the precision for
* \return precision p_n
*/
double precision(Hypothesis* C)
{
	// TODO
	return 0;
}

/**
*
*
* \return Brevity Penalty
*/
double brevity_penalty()
{
	// TODO
	return 0;
}

/**
*
*
* \return BLEU_score
*/
double BLEU_score()
{
	// TODO
	return 0;
}

/**
* Rates if the translation (trans) by comparing it to a human translation (target)
*
* \param trans	translation done by machine
* \param target	translation done by human
* \return 	rating
*/
double rate(string &trans, string &target)
{
	//TODO
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
	vector<struct trans_struct> trans_vec;
	trans_vec.resize(VECTOR_INIT_SIZE);
	string trans_line, target_line;

	// read trans_tab into trans_tab_vec
	while (getline(trans, trans_line) && getline(trans, target_line))
	{
		struct trans_struct current;
		current.trans = trans_line;
		current.target = target_line;
		current.rate = rate(trans_line, target_line);
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

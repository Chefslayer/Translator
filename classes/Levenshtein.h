#ifndef __LEVENSHTEIN_H__
#define __LEVENSHTEIN_H__
#include <string>
using namespace std;

class Levenshtein
{
	/**
	* calcs the levenshtein distance
	*
	* \param &trans		translation by machine
	* \param &target	translation by human
	* \return 
	*/
	unsigned int levenshtein_distance(string &trans, string &target);
};
#endif

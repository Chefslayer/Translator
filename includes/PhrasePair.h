/**
 * @file
 * @author  Gruppe 2
 * @version 1.0
 *
 * @section DESCRIPTION
 *
 * The PhrasePair struct holds a pair of a phrase in src-lang <-> target-lang.
 */

#ifndef PHRASEPAIR_H
#define PHRASEPAIR_H

#include <vector>

using namespace std;

/**
 * The PhrasePair struct holds a pair of a phrase in src-lang <-> target-lang.
 */
struct PhrasePair
{
	/// phrase in source lang
	vector<unsigned int> src;

	/// phrase in target lang
	vector<unsigned int> target;

	/**
	 * inits a new PhrasePair with given values.
	 *
	 * \param s vector with the words of the phrase in source language
	 * \param t vector with the words of the phrase in target language
	 */
	PhrasePair(vector<unsigned int> &s, vector<unsigned int> &t);
};
#endif

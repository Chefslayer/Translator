/**
 * @file
 * @author  Gruppe 2
 * @version 1.0
 *
 * @section DESCRIPTION
 *
 * The Levenshtein class calculates the Levenshtein-Distance for a translation.
 */
#ifndef __LEVENSHTEIN_H__
#define __LEVENSHTEIN_H__
#include <vector>
#include <string>
#include "Lexicon.h"

using namespace std;

/**
 * The Levenshtein class calculates the Levenshtein-Distance for a translation.
 * The Levenshtein class calculates the Levenshtein-Distance for a translation, by setting up a matrix and filling it bit by bit with dynamic programing.
 */
class Levenshtein{
	private:
		vector<vector<unsigned int> > matrix;
		vector<unsigned int> trans_v, ref_v;
	public:
		/**
		 * Constructor inits and fills the distance-matrix.
		 *
		 * \param trans translation
		 * \param ref reference
		 */
		Levenshtein(vector<unsigned int> trans, vector<unsigned int> ref);

		/**
		 * gets the last entry in the matrix.
		 *
		 * \return Levenshtein-Distance
		 */
		unsigned int getDistance();

		/**
		 * returns a string with the path operations and additionally the words that were deleted/inserted/matched.
		 *
		 * \param lex Lexicon to look up the words.
		 * \return the path with words of operations.
		 */
		string getPath(Lexicon &lex);

		/**
		 * Gets all operations that have been done: d=delete, i=insert, m=maching.
		 *
		 * \return the path of operations.
		 */
		string getPathOps();
};
#endif

/**
 * @file
 * @author  Gruppe 2
 * @version 1.0
 *
 * @section DESCRIPTION
 *
 * This file implements the Alignment Class, which handels the reading for a alignment-file.
 */

#ifndef __ALIGNMENT_H__
#define __ALIGNMENT_H__

#include <vector>

using namespace std;

/**
 * This file implements the Alignment Class, which handels the reading for a alignment-file.
 */
class Alignment
{
	private:
		/// holds the alignment-matrix
		vector<vector<bool> > matrix;

		/// current sentence
		unsigned int sentenceNum = 0;

		/// Lexicon for the words of the source language
		Lexicon*	f,
		/// Lexicon for the words of the target language
				e;
	public:

		/// the file with the alignment
		igzstream file;

		/// Constructor inits the class
		Alignment(igzstream file);

		/** sets up the class for for the next sentence
		 *
		 * \param srcLength length of the source-sentence
		 * \param targetLength length of the target-sentence
		 */
		nextSentence(unsigned int srcLength, unsigned int targetLength);

		/** inits the matrix
		 *
		 * \param srcLength length of the source-sentence
		 * \param targetLength length of the target-sentence
		 */
		initMatrix(unsigned int srcLength, unsigned int targetLength);

		/** first aligned word in target lang.
		 *
		 * \param j1 first pointer in source sentence
		 * \param j2 second pointer in source sentence
		 * \return first aligned word in target lang
		 */
		unsigned int getMinTargetAlig(unsigned int j1, unsigned int j2);

		/** last aligned word in target lang.
		 *
		 * \param j1 first pointer in source sentence
		 * \param j2 second pointer in source sentence
		 * \return last aligned word in target lang
		 */
		unsigned int getMaxTargetAlig(unsigned int j1, unsigned int j2);

		/** first aligned word in source lang.
		 *
		 * \param i1 first pointer in target sentence
		 * \param i2 second pointer in target sentence
		 * \return first aligned word in source lang
		 */
		unsigned int getMinSrcAlig(unsigned int i1, unsigned int i2);

		/** last aligned word in source lang.
		 *
		 * \param i1 first pointer in target sentence
		 * \param i2 second pointer in target sentence
		 * \return last aligned word in source lang
		 */
		unsigned int getMaxSrcAlig(unsigned int i1, unsigned int i2);

		/** Outputs a phrase
		 *
		 * \param j1 first pointer in source sentence
		 * \param j2 second pointer in source sentence
		 * \param i1 first pointer in target sentence
		 * \param i2 second pointer in target sentence
		 * \return a vector of words. seperator element is 0.
		 *	example:
		 *	v[0]=871, v[1]=831,
		 *	v[2]=0,
		 *	v[3]=11, v[4]=134
		 */
		vector<unsigned int> outputPhrase(unsigned int j1, unsigned int j2, unsigned int i1, unsigned int i2);
};
#endif

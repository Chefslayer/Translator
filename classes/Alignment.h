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
#include <string>
#include "../lib/gzstream.h"
#include "../includes/PhrasePair.h"

using namespace std;

/**
 * This file implements the Alignment Class, which handels the reading for a alignment-file.
 */
class Alignment
{
	private:
		/// holds the alignment for the source lang
		vector<unsigned int> srcVec;

		/// holds the alignment for the target lang
		vector<unsigned int> targetVec;

		/// current sentence
		unsigned int sentenceNum;

		/// length of the current source-line
		unsigned int srcLength;

		/// length of the current target-ine
		unsigned int targetLength;
	public:
		/// the file with the alignment
		char* fileName;

		/// the file-stream with the alignment
		igzstream* file;

		/** Constructor inits the class
		 *
		 * \param fileName the alignment file
		 * \throws bool openFileFail if the file cannot be opened
		 */
		Alignment(char* fileName);

		/** sets up the class for for the next sentence
		 *
		 * \param srcLength length of the source-sentence
		 * \param targetLength length of the target-sentence
		 */
		void nextSentence(unsigned int srcLength, unsigned int targetLength);

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
		 * \param srcWords words of the source line
		 * \param targetWords words of the target line
		 * \return a PhrasePair which contains the words of the phrase in src and target lang
		 */
		PhrasePair* outputPhrase(unsigned int j1, unsigned int j2, unsigned int i1, unsigned int i2, vector<unsigned int> &srcWords, vector<unsigned int> &targetWords);
};
#endif

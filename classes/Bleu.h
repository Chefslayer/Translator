/**
 * @file
 * @author  Gruppe 2
 * @version 1.0
 *
 * @section DESCRIPTION
 *
 * The Bleu class calculates the BLEU-Score rating for a translation.
 */

#ifndef __BLEU_H__
#define __BLEU_H__

#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include "../includes/functions.h"

using namespace std;

/**
 * The Bleu class calculates the BLEU-Score rating for a translation.
 * The Bleu class calculates the bleuScore rating for a translation, by computing the brevityPenalty, precision and nGramsMatching / nGrams.
 */
class Bleu
{
	private:
		/// holds the words of the translation
		vector<unsigned int>	trans,
		/// holds the words of the reference
					ref;
	public:
		/**
		 * Constructor sets up the initial values.
		 *
		 * \param translation
		 * \param reference
		 */
		Bleu(vector<unsigned int> translation, vector<unsigned int> reference);

		/**
		 * Counts all matching n-grams in the Hypothesis and it's reference.
		 *
		 * \param n length of word-sequence
		 * \return
		 */
		int nGramsMatching(unsigned int n);

		/**
		 * calcs the precision of a Hypothesis with n-grams.
		 *
		 * \param n count of grams
		 * \return precision p_n
		 */
		double precision(unsigned int n);

		/**
		 * calcs the Brevity Penalty.
		 *
		 * \return Brevity Penalty
		 */
		double brevityPenalty();

		/**
		 * calcs the BLEU-score for a hypothesis.
		 *
		 * \param N
		 * \return BLEU_score
		 */
		double bleuScore(unsigned int N);
};
#endif

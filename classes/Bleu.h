#ifndef __BLEU_H__
#define __BLEU_H__

#include <string>
#include <vector>
#include <math.h>
#include "../includes/functions.h"

using namespace std;

class Bleu
{
	private:
		unsigned int transWord, refWord;
		vector<unsigned int> trans, ref;
	public:
		/** Constructor
		*
		* \param translation
		* \param reference
		* \return
		*/
		Bleu(vector<unsigned int> translation, vector<unsigned int> reference); // wenn ich Referenzen benutze compiliert es nicht mehr^^

		/**
		* Counts all matching n-grams in the Hypothesis and it's reference
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
		*
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

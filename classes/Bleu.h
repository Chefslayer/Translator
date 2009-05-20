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
		string trans_str, ref_str;
		vector<string> trans, ref;
	public:
		/** Constructor
		*
		* \param translation
		* \param reference
		* \return
		*/
		Bleu(string &translation, string &reference);

		/**
		* Counts all n-grams for a hypothesis and it's reference
		*
		* \param n length of word-sequence
		* \return
		*/
		unsigned int count_n_grams(unsigned int n);

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
		double brevity_penalty();

		/**
		* calcs the BLEU-score for a hypothesis.
		*
		* \param N
		* \return BLEU_score
		*/
		double BLEU_score(unsigned int N);
};
#endif

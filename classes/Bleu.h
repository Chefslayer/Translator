#ifndef __BLEU_H__
#define __BLEU_H__
#include <math.h>
#include <iostream>
#include "../includes/hypothesis.h"

using namespace std;

class Bleu
{
	public:
		unsigned int count_n_grams(unsigned int n, Hypothesis* H);

		/**
		* calcs the precision of a Hypothesis with n-grams
		*
		* \param C reference to the Hypothesis to calc the precision for
		* \param n count of grams
		* \return precision p_n
		*/
		double precision(Hypothesis* C, unsigned int n);

		/**
		*
		*
		* \return Brevity Penalty
		*/
		double brevity_penalty(unsigned int c,unsigned int r);

		/**
		* calcs the BLEU-score for a Hypothesis
		*
		* \param N
		* \param H reference to a Hypothesis to calc the BLEU-score for
		* \return BLEU_score
		*/
		double BLEU_score(unsigned int N, Hypothesis* H,unsigned int c,unsigned int r);
};
#endif

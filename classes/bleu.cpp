#include <math.h>
#include <iostream>
#include "../includes/hypothesis.h"


using namespace std;

unsigned int count_n_grams(unsigned int n, Hypothesis* H)
{
	// TODO
 	return 0;
}

	/**
	* calcs the precision of a Hypothesis with n-grams
	*
	* \param C reference to the Hypothesis to calc the precision for
	* \param n count of grams
	* \return precision p_n
	*/
double precision(Hypothesis* C, unsigned int n)
{
	// TODO
	return 0;
}

	/**
	*
	*
	* \return Brevity Penalty
	*/
double brevity_penalty(unsigned int c,unsigned int r)
{
	if (c > r)
		return 1;
	if (c <= r)
		return exp((double)(1-r)/ (double)c);
	else
		return 0;
}

	/**
	* calcs the BLEU-score for a Hypothesis
	*
	* \param N
	* \param H reference to a Hypothesis to calc the BLEU-score for
	* \return BLEU_score
	*/
double BLEU_score(unsigned int N, Hypothesis* H,unsigned int c,unsigned int r)
{
	if (N==0)
	{
		cerr << "BLEU_score: invalid N" << endl;
	return 0;
	}
/* um die Summe zu berechnen:
 * 1. 1/N kann man ausklammern
 * 2. log(a)+log(b) = log(a*b) => es reicht die p_n zu multiplizieren und am Ende einmal den log zu berechnen.
*/
double akku=0;
for (unsigned int i=1; i<=N; i++)
akku *= precision(H, i);

		return brevity_penalty(c, r)*exp(log(akku)/(double)N);
		}

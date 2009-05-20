#include <math.h>
#include <iostream>
#include "Bleu.h"
#include "../includes/hypothesis.h"
using namespace std;

unsigned int Bleu::count_n_grams(unsigned int n, Hypothesis* H)
{
	// TODO
 	return 0;
}

double Bleu::precision(Hypothesis* C, unsigned int n)
{
	// TODO
	return 0;
}

double Bleu::brevity_penalty(unsigned int c,unsigned int r)
{
	if (c > r)
		return 1;
	if (c <= r)
		return exp((double)(1-r)/ (double)c);
	else
		return 0;
}

double Bleu::BLEU_score(unsigned int N, Hypothesis* H,unsigned int c,unsigned int r)
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

#include <string>
#include <vector>
#include <math.h>
#include "Bleu.h"
#include "../includes/functions.h"

using namespace std;

Bleu::Bleu(vector<unsigned int> translation, vector<unsigned int> reference)
{
	trans = translation;
	ref = reference;
}

unsigned int Bleu::count_n_grams(unsigned int n)
{
	// TODO
 	return 0;
}

unsigned int Bleu::count_matching_n_grams(unsigned int n)
{
	return 1;
}
double Bleu::precision(unsigned int n)
{
	// TODO
	return 1;
}

double Bleu::brevity_penalty()
{
	unsigned int c = this->trans.size();
	unsigned int r = this->ref.size();

	if (c > r)
		return 1;
	if (c <= r)
		return exp((double)(1-r)/(double)c);
	else
		return 0;
}

double Bleu::BLEU_score(unsigned int N)
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
	double akku=1;
	for (unsigned int i=1; i<=N; i++)
		akku *= precision(i);
	return brevity_penalty()*exp(log(akku)/(double)N);
}

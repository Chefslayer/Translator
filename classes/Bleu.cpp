#include <iostream>
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

int Bleu::nGramsMatching(unsigned int n)
{
	int num = 0;
	for (int i = 0; i + n < ref.size(); i++)
	{
		for (int transposition = 0; transposition + n < trans.size(); transposition++)
		{
			if (trans[transposition] == ref[i])
			{
				int j=1;
				while (		j < n
						&& (i+j) < ref.size()
						&& (transposition + j) < trans.size()
						&& trans[transposition + j] == ref[i + j]
				      								) j++;
				if (j == n)
				{
					num++;
					break;
				}
			}
		}
	}
	return num;
}

double Bleu::precision(unsigned int n)
{
	double precision = 0;
	if ((ref.size() + 1 - n) <= 0)
	{
		cerr << "Bleu::precision: Division durch 0." << endl;
		return -1;
	}
	precision = (double)nGramsMatching(n)/(double)(trans.size() + 1 - n);
	return precision;
}

double Bleu::brevityPenalty()
{
	int c = this->trans.size();
	int r = this->ref.size();

	if (c > r)
		return 1;
	if (c > 0) // (c <= r) gilt hier eh
		return (double)exp(((double)(1-r)/(double)c));

	cerr << "Bleu::brevityPenalty(): Fehler bei der Berechnung. (Länge der Referenzübersetzung <= 0)" << endl;
	return -1;
}

double Bleu::bleuScore(unsigned int N)
{
	if (N==0)
	{
		cerr << "Bleu::bleuScore: ungültiges N (0)" << endl;
		return 0;
	}
	/* um die Summe zu berechnen:
 	* 1. 1/N kann man ausklammern
	* 2. log(a)+log(b) = log(a*b) => es reicht die p_n zu multiplizieren und am Ende einmal den log zu berechnen.
	*/
	double akku = 1.0;
	for (unsigned int i=1; i<=N; i++)
	{
	//	akku += log((double)precision(i));
		akku *= precision(i);
	//	cout << "precision:" << precision(i) << endl;
	}
	return brevityPenalty()*exp(log(akku)/(double)N);
}

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
	unsigned int temp = 0;
	for (int i = 0; i < ref.size();i++)
	{
		for (int transposition = 0; transposition < trans.size(); transposition++)
		{
			if (trans[transposition] == ref[i])
			{
				temp = 1;
				for (int j = 1; j < n; j++)
				{
					if ((i+j) >= ref.size() or (transposition + j) >= trans.size())
					{
						break;
					}
					else
						if (trans[transposition + j] == ref[i + j]) temp++;
				}
			if (temp == n)
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
		cout << "Hilfe durch 0 teilen!!!!" << endl;
		return -1;
	}
	precision = (double)nGramsMatching(n)/(double)(ref.size() + 1 - n);
	return precision;
}

double Bleu::brevityPenalty()
{
	int c = this->trans.size();
	int r = this->ref.size();

	if (c > r)
		return 1;
	if (c <= r)
	{
		//cout << "r:" << (double)r << "c:" << (double)c << "(1-r)/c:" << (double)(1-r)/(double)c <<  endl;
		if (c <= 0)
			cout << "Die Länge der Referenzübersetzung ist <= 0..." << endl;
		return (double)exp(((double)(1-r)/(double)c));
	}
//	else
//		return 0;
}

double Bleu::bleuScore(unsigned int N)
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
	double akku = 1.0;
	for (unsigned int i=1; i<=N; i++)
	{
	//	akku = akku + log((double)precision(i));
	akku = akku * precision(i);
	//	cout << "precision:" << precision(i) << endl;
	}
		return brevityPenalty()*exp(log(akku)/(double)N);
}

#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <algorithm>
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
	vector<bool>bitvec; // saves whether a ref-ngram  is already used or not.
	bitvec.resize(ref.size(),0);

	unsigned int nGramsMatchingCount=0;
	
	for (unsigned int i=0; i+n-1<trans.size(); i++)
	{
		for (unsigned int j=0; j+n-1<ref.size(); j++)
		{
			if (bitvec[j]==0) // this ngram in the ref is not used yet
			{
				//check if ngrams match
				unsigned int pos = 0;
				while (	pos < n
					&& trans[i+pos] == ref[j+pos]
				      							) pos++;
				if (pos == n)
				{
					// matched
					nGramsMatchingCount++;
	
					// mark ngram in reference as used in the bitvector
					bitvec[j]=1;
					
					// dont count more occurrences in ref for this trans-ngram
					break; // for (..j..)
				}
			}
		}
	}
	return nGramsMatchingCount;
}

double Bleu::precision(unsigned int n)
{
	int nGrams = trans.size() + 1 - n;
	// we dont expect nGrams<=0 here, since we're not going to calc the precisions if there are no ngrams for this n
	/*if ( nGrams <= 0)
	{
		// was wenn nGrams < 0 ?
		cerr << "Bleu::precision: Division durch 0." << endl;
		return 1;
	}*/
	return (double)nGramsMatching(n)/(double)nGrams;
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

	// maybe there are less words in the trans or ref than we would try to get n-grams for.. so we search for the maximum N we can use here.
	unsigned int maxN = min(min(N, trans.size()-1), ref.size()-1);
	
	for (unsigned int i=1; i<=maxN; i++)
	{
		akku *= precision(i);
	}
	if (akku<=0)
		return 0;
	return brevityPenalty()*exp(log(akku)/(double)maxN);
}

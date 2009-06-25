/**
 *@file
 *@author Gruppe 2
 *@version 1.0
 *
 * @section DESCRIPTION
 *
 * The Alignment class extracts phrasepairs out of an given alignment
 */

#include "Alignment.h"
#include <vector>
#include <string>
#include "../lib/gzstream.h"
#include "../includes/PhrasePair.h"

using namespace std;


Alignment::Alignment(char* fileName)
{
	this->fileName = fileName;
	file = new igzstream(fileName);
	if (!file->good())
	{
		// exception openFileFail
		throw 1;
	}
	else
	{
		// read the first "SENT: x" from the alignment
		string word;
		*file >> word; // SENT:
		*file >> sentenceNum; // x
	}
}


/**
 * reads the needed information of the alignment for the current sentence
 *
 * \param srcLength the length of the sentence is sourcelanguage
 * \param targetLength the length of the sentence in sourcelanguage
 */

void Alignment::nextSentence(unsigned int srcLength, unsigned int targetLength)
{
	this->srcLength = srcLength;
	this->targetLength = targetLength;

	aligVec.clear();

	// read the alignment for the current sentence
	unsigned int srcWordNum, destWordNum;
	string word;
	while (*file >> word)
	{
		if (word == "SENT:")
		{
			*file >> sentenceNum;
			break;
		}
		else
		{
			*file >> srcWordNum;
			*file >> destWordNum;
			aligVec.push_back(pair<unsigned int, unsigned int> (srcWordNum, destWordNum));
		}
	}
}

/**
 * finds the minimum in the targetsentence between j1 and j2
 *
 * \param j1
 * \param j2
 * \return min the minimum in the targetsentence
 */
unsigned int Alignment::getMinTargetAlig(unsigned int j1, unsigned int j2)
{
	unsigned int min=this->targetLength;

	for (vector<pair<unsigned int, unsigned int> >::iterator it=aligVec.begin(); it!=aligVec.end(); it++)
	{
		if (it->first>=j1 && it->first<=j2 && // j1 <= src <= j2
			it->second<min)
			min = it->second;
	}
	return min;
}
/**
 * finds the minimum in the targetsentence between j1 and j2
 *
 * \param j1
 * \param j2
 * \return max the maximum in the targetsentence
 */
unsigned int Alignment::getMaxTargetAlig(unsigned int j1, unsigned int j2)
{
	unsigned int max=0;

	for (vector<pair<unsigned int, unsigned int> >::iterator it=aligVec.begin(); it!=aligVec.end(); it++)
	{
		if (it->first>=j1 && it->first<=j2 && // j1 <= src <= j2
			it->second>max
		)
			max = it->second;
	}
	return max;
}

/**
 * finds the minimum in the sourcesentence between i1 and i2
 *
 * \param i1
 * \param i2
 * \return min the minimum in the sourcesentence
 */
unsigned int Alignment::getMinSrcAlig(unsigned int i1, unsigned int i2)
{
	unsigned int min=this->srcLength;

	for (vector<pair<unsigned int, unsigned int> >::iterator it=aligVec.begin(); it!=aligVec.end(); it++)
	{
		if (it->second>=i1 && it->second<=i2 && // i1 <= target <= i2
			it->first<min
		)
			min = it->first;
	}
	return min;
}

/**
 * finds the maximum in the sourcesentence between i1 and i2
 *
 * \param i1
 * \param i2
 * \return max the maximum in the sourcesentence
 */
unsigned int Alignment::getMaxSrcAlig(unsigned int i1, unsigned int i2)
{
	unsigned int max=0;

	for (vector<pair<unsigned int, unsigned int> >::iterator it=aligVec.begin(); it!=aligVec.end(); it++)
	{
		if (it->second>=i1 && it->second<=i2 && // i1 <= target <= i2
			it->first>max
		)
			max = it->first;
	}
	return max;
}

/**
 *
 * creates a Phrasepair containing the source and the target phrase and returns it
 * \param j1
 * \param j2
 * \param i1
 * \param i2
 * \param srcWords the sourcesentence
 * \param targetWords the targetsentence
 * \return phrasePair a pair containing the source and the target phrase
 */

PhrasePair* Alignment::outputPhrase(unsigned int j1, unsigned int j2, unsigned int i1, unsigned int i2, vector<unsigned int> &srcWords, vector<unsigned int> &targetWords)
{
	vector<unsigned int> src, target;
	src.resize(j2-j1+1);
	target.resize(i2-i1+1);

	// j = column
	for (unsigned int j=j1; j<=j2; j++)
	{
		src[j-j1] = srcWords[j];
	}
	// i = row
	for (unsigned int i=i1; i<=i2; i++)
	{
		target[i-i1] = targetWords[i];
	}

	return new PhrasePair(src, target);
}

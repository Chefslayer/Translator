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

unsigned int Alignment::getMinTargetAlig(unsigned int j1, unsigned int j2)
{
	unsigned int min=this->targetLength;

	for (vector<pair<unsigned int, unsigned int> >::iterator it=aligVec.begin(); it!=aligVec.end(); it++)
	{
		if (it->first>=j1 && it->first<=j2 && // j1 <= src <= j2
			it->second<min
		)
			min = it->second;
	}
	return min;
}

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

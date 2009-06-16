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

	srcVec.clear();
	targetVec.clear();

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
			srcVec.push_back(srcWordNum);
			targetVec.push_back(destWordNum);
		}
	}
}

unsigned int Alignment::getMinTargetAlig(unsigned int j1, unsigned int j2)
{
	unsigned int min=this->targetLength;

	for (unsigned int k=0; k<srcVec.size(); k++)
	{
		if (srcVec[k]>=j1 && srcVec[k]<=j2 && // j1 <= src <= j2
			targetVec[k]<min
		)
			min = targetVec[k];
	}
	return min;
}

unsigned int Alignment::getMaxTargetAlig(unsigned int j1, unsigned int j2)
{
	unsigned int max=0;

	for (unsigned int k=0; k<srcVec.size(); k++)
	{
		if (srcVec[k]>=j1 && srcVec[k]<=j2 && // j1 <= src <= j2
			targetVec[k]>max
		)
			max = targetVec[k];
	}
	return max;
}

unsigned int Alignment::getMinSrcAlig(unsigned int i1, unsigned int i2)
{
	unsigned int min=this->srcLength;

	for (unsigned int k=0; k<targetVec.size(); k++)
	{
		if (targetVec[k]>=i1 && targetVec[k]<=i2 && // i1 <= target <= i2
			srcVec[k]<min
		)
			min = srcVec[k];
	}
	return min;
}

unsigned int Alignment::getMaxSrcAlig(unsigned int i1, unsigned int i2)
{
	unsigned int max=0;

	for (unsigned int k=0; k<targetVec.size(); k++)
	{
		if (targetVec[k]>=i1 && targetVec[k]<=i2 && // i1 <= target <= i2
			srcVec[k]>max
		)
			max = srcVec[k];
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

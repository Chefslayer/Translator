#include "Alignment.h"
#include <vector>
#include <string>
#include "../lib/gzstream.h"
#include "../includes/PhrasePair.h"

using namespace std;

Alignment::Alignment(char* fileName)
{
	this->fileName = fileName;
	igzstream file(fileName);
	if (!file.good())
	{
		// exception openFileFail
		throw 1;
	}
	else
	{
		// read the first "SENT: x" from the alignment
		this->file = &file;
		string word;
		file >> word; // SENT:
		file >> sentenceNum;
	}
}

void Alignment::nextSentence(unsigned int srcLength, unsigned int targetLength)
{
	initMatrix(srcLength, targetLength);
	unsigned int srcWordNum, destWordNum;
	string word;
	while (*file >> word)
	{
		if (word == "SENT:")
		{
			sentenceNum++;
			break;
		}
		else
		{
			*file >> srcWordNum;
			*file >> destWordNum;
			matrix[srcWordNum][destWordNum] = 1;
		}
	}
}

void Alignment::initMatrix(unsigned int srcLength, unsigned int targetLength)
{
	matrix.resize(srcLength);
	for (unsigned int i=0; i<matrix.size(); i++)
		matrix[i].resize(targetLength, 0);
}

unsigned int Alignment::getMinTargetAlig(unsigned int j1, unsigned int j2)
{
	unsigned int min=matrix[0].size()-1; // maximum length of a column

	// j = column
	for (unsigned int j=j1; j<=j2; j++)
	{
		// i = entry in the j-column
		unsigned int i=0;
		while (i<matrix[j].size()-1 && matrix[j][i]==0)
			i++;
		if (matrix[j][i]==1 && i<min)
		{
			min = i;
		}
	}
	return min;
}

unsigned int Alignment::getMaxTargetAlig(unsigned int j1, unsigned int j2)
{
	unsigned int max=0; // minimum of a column

	// j = column
	for (unsigned int j=j1; j<=j2; j++)
	{
		// i = entry in the j-column
		unsigned int i=matrix[i].size()-1; // maximum length of a column
		while (i>0 && matrix[j][i]==0)
			i--;
		if (matrix[j][i]==1 && i>max)
		{
			max = i;
		}
	}
	return max;
}

unsigned int Alignment::getMinSrcAlig(unsigned int i1, unsigned int i2)
{
	unsigned int min=matrix.size()-1; // maximum length of a row

	// i = row
	for (unsigned int i=i1; i<=i2; i++)
	{
		// j = entry in the i-row
		unsigned int j=0;
		while (j<matrix.size()-1 && matrix[j][i]==0)
			j++;
		if (matrix[j][i]==1 && j<min)
		{
			min = j;
		}
	}
	return min;
}

unsigned int Alignment::getMaxSrcAlig(unsigned int i1, unsigned int i2)
{
	unsigned int max=0; // minimum of a row

	// i = row
	for (unsigned int i=i1; i<=i2; i++)
	{
		// j = entry in the i-row
		unsigned int j=matrix.size()-1; // maximum length of a row
		while (j>0 && matrix[j][i]==0)
			j--;
		if (matrix[j][i]==1 && j>max)
		{
			max = j;
		}
	}
	return max;
}

PhrasePair* Alignment::outputPhrase(unsigned int j1, unsigned int j2, unsigned int i1, unsigned int i2)
{
	vector<unsigned int> src, target;

	// ...TODO...

	return new PhrasePair(src, target);
}

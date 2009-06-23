#include <string>
#include <vector>
#include <map>
#include "../includes/functions.h"
#include "Lexicon.h"
#include "SingleCount.h"
#include "../includes/constants.h"

using namespace std;

Lexicon::Lexicon()
{
	i = 0; // number of inserted words
	vector<string> int2strAssignment(VECTOR_INIT_SIZE, "");
	insertWord("(?)");
}

unsigned int Lexicon::insertWord(string word)
{
	// insert word in str2intAssignment
	pair<map<string,unsigned int>::iterator, bool> temp = str2intAssignment.insert(pair<string,unsigned int> (word,i)); //returns an iterator and a bool which is false if the same word has alredy been inserted
	
	if (temp.second) // is the word new to the assignment
	{
		// word is new
		if (i >= int2strAssignment.size()) // resize vector if necessary
			{
				int2strAssignment.resize(int2strAssignment.size() + VECTOR_RESIZE);
			}
		// insert word in int2strAssignment
		int2strAssignment[i] = word;
		i++;
		return (i-1);
	}
	else
	{
		// word is already inserted in both assignments
		return (*temp.first).second;
	}
}

vector<unsigned int> Lexicon::insertSentence(vector<string> words, SingleCount* singlesObject)
{
	vector<unsigned int> result(words.size(), 0);
	// put all words of the sentence in source language-lexicon and the value of the word into the lang-object
	unsigned int i;
	for (i=0; i < words.size(); i++)
	{
		unsigned int val = this->insertWord(words[i]);
		// nur zählen wenn auch ein SingleCount objekt übergeben wurde
		if (singlesObject != NULL)
			singlesObject->insert(val);
		result[i] = val;
	}
	return result;
}

vector<unsigned int> Lexicon::insertSentence(string line, SingleCount* singlesObject)
{
	vector<string> words = stringSplit(line, " ");
	return this->insertSentence(words, singlesObject);
}

string Lexicon::getWord(unsigned int value)
{
	if (value >= int2strAssignment.size())
		return "?";
	string re = int2strAssignment[value];
	return re;
}

unsigned int Lexicon::getNum(string word)
{
	return (str2intAssignment.find(word))->second;
}

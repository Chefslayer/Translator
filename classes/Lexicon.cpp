// Implementierung
#include "Lexicon.h"
#include "../includes/constants.h"
#include <string>
#include <vector>
#include <map>
using namespace std;

Lexicon::Lexicon(string lang)
{
	language = lang;
	i = 0; //number of inserted words
	vector<string> int2str(VECTOR_INIT_SIZE, "");
	insert("(?)");
}

/**
inserts a word in the lexicon
\param word inserts the word
\return the value of the word
*/
unsigned int Lexicon::insert(string word)
{
	pair<map<string,unsigned int>::iterator, bool> temp = str2int.insert(pair<string,unsigned int> (word,i));
	if(temp.second) //has word alredy been inserted?
	{
		if (i >= int2str.size())
		{
			int2str.resize(int2str.size() + VECTOR_RESIZE);
		}

		// word has been inserted
		int2str[i] = word;
		i++;
		return (i-1);
	}
	else
	{
		// word is already saved
		return (*temp.first).second;
	}
}
/**
* Get Word by Code
* \param value 
* \return word für given code
*/
string Lexicon::getWord(unsigned int value)
{
	if (value >= int2str.size())
		return "?";
	string re = int2str[value];
	return re;
}

/**
* get code for word
* \param word string wich will be convertet into a int
* \return code
*/

unsigned int Lexicon::getNum(string word)
{
	return (str2int.find(word))->second;
}

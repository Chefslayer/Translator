#ifndef __LEXICON_H__
#define __LEXICON_H__

#include "Lexicon.h"
#include "../includes/constants.h"
#include "SingleCount.h"
#include <string>
#include <vector>
#include <map>

using namespace std;

class Lexicon
{
	private:
		unsigned int i;
		map<string,unsigned int> str2intAssignment;
		vector<string> int2strAssignment;
		string language;
	public:
		Lexicon();
		
		/*
		inserts a word in the lexicon
		returns the value of the word
		*/
		unsigned int insertWord(string word);


		vector<unsigned int> insertSentence(string line, SingleCount *singlesObject = NULL);

		/*
		 *Get associated word for value
		 */ 
		
		string getWord(unsigned int value);
		/*
		 *Get associated value for word
		 */
		unsigned int getNum(string word);
};
#endif

#ifndef __LEXICON_H__
#define __LEXICON_H__

#include "Lexicon.h"
#include "../includes/constants.h"
#include <string>
#include <vector>
#include <map>

using namespace std;

class Lexicon
{
	private:
		unsigned int i;
		map<string,unsigned int> str2int;
		vector<string> int2str;
		string language;
	public:
		Lexicon();
		
		/*
		inserts a word in the lexicon
		returns the value of the word
		*/
		unsigned int 	insert(string word);

		/*
		 *Get associated word for value
		 */ 
		
		string 			getWord(unsigned int value);
		/*
		 *Get associated value for word
		 */
		unsigned int 	getNum(string word);
};
#endif

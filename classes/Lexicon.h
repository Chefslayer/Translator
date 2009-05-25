/**
 * @file
 * @author  Gruppe 2
 * @version 1.0
 *
 * @section DESCRIPTION
 *
 * The Lexicon class holds all words for a specific language and maps them to int values.
 */

#ifndef __LEXICON_H__
#define __LEXICON_H__

#include <string>
#include <vector>
#include <map>
#include "SingleCount.h"

using namespace std;


/**
 * The Lexicon class holds all words and them to int values.
 * The Lexicon class holds all words for a specific language and maps them to int values.
 */
class Lexicon
{
	private:
		/// number of inserted words
		unsigned int i;
		map<string,unsigned int> str2intAssignment;
		vector<string> int2strAssignment;
	public:
		/**
		 * inits a new lexicon
		 */
		Lexicon();
		
		/**
		 * inserts a word in the lexicon
		 *
		 * \param word inserts the word
		 * \return the value of the word
		 */
		unsigned int insertWord(string word);

		/**
		 * gets a line already splitted by " " and saved to a vector (words) and a singleCount* object and puts all words of the sentence in the lexicon and saves the word-values in the singlesObject
		 *
		 * \param line a vector with the words of the sentence
		 * \param singlesObject the SingleCount* Object to count the singles (optional)
		 * \return a vector with the sentence in values
		 */
		vector<unsigned int> insertSentence(vector<string> words, SingleCount* singlesObject = NULL);

		/**
		 * gets a line and a singleCount* object and puts all words of the sentence in the lexicon and saves the word-values in the singlesObject
		 *
		 * \param line a sentence
		 * \param singlesObject the SingleCount* Object to count the singles (optional)
		 * \return a vector with the sentence in values
		 */
		vector<unsigned int> insertSentence(string line, SingleCount* singlesObject = NULL);

		/**
		 * Get associated word for a given code
		 *
		 * \param value
		 * \return word for given code
		 */
		string getWord(unsigned int value);
		
		/**
		 * Get associated code for a given word
		 *
		 * \param word string wich will be convertet into an int
		 * \return code
		 */
		unsigned int getNum(string word);
};
#endif

/**
 * @file
 * @author  Gruppe 2
 * @version 1.0
 *
 * @section DESCRIPTION
 *
 * The SingleCount class holds and counts the occurrence of single-words.
 */

#ifndef __SINGLECOUNT_H__
#define __SINGLECOUNT_H__
#include "../includes/constants.h"
#include <vector>

using namespace std;

/**
 * The SingleCount class holds and counts the occurrence of single-words.
 */
class SingleCount
{
	private:
		vector<unsigned int> wordcounts;
	public:
		/**
		 * Constructor inits the wordcounts vector size
		 */
		inline SingleCount()
		{
			vector<unsigned int> wordcounts(VECTOR_INIT_SIZE, 0);
		}

		/**
		 * inserts and/or increments the count of a single-word.
		 *
		 * \param word word to insert
		 */
		inline void insert(unsigned int word)
		{
			if (word >= wordcounts.size())
			{
				wordcounts.resize(wordcounts.size() + VECTOR_RESIZE);
			}
			wordcounts[word]++;
		}

		/**
		 * gets the count of occurrence of a word.
		 *
		 * \param word the word to get the count for.
		 * \return count of occurrence of the given word.
		 */
		inline unsigned int getFreq(unsigned int word)
		{
			return wordcounts[word];
		}

		/**
		 * gets the count of inserted words.
		 *
		 * \return count of inserted words = size of the wordcounts-map.
		 */
		inline unsigned int getSize()
		{
			return wordcounts.size();
		}
};
#endif

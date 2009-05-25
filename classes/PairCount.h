/**
 * @file
 * @author  Gruppe 2
 * @version 1.0
 *
 * @section DESCRIPTION
 *
 * The PairCount class holds and counts the occurrence of word-pairs.
 */

#ifndef __PAIRCOUNT_H__
#define __PAIRCOUNT_H__

#include <map>
#include <utility>

using namespace std;

/**
 * The PairCount class holds and counts the occurrence of word-pairs.
 */
class PairCount
{
	private:
		map<pair<unsigned int, unsigned int>, unsigned int> pairCounts;
		map<pair<unsigned int, unsigned int>, unsigned int>::iterator it;
	public:
		/**
		 * inserts and/or increments the count of a word-pair.
		 *
		 * \param wordpair the word-pair to insert
		 */
		inline void insert(pair<unsigned int, unsigned int> wordpair)
		{
			pairCounts[wordpair]++;
		}

		/**
		 * gets the count of occurrence of a word-pair.
		 *
		 * \param wordpair the word-pair to get the count for.
		 * \return count of occurrence of the given word pair.
		 */
		inline unsigned int getFreq(pair<unsigned int, unsigned int> wordpair)
		{
			return (pairCounts.find(wordpair))->second;
		}

		/**
		 * gets the count of inserted pairs.
		 *
		 * \return count of inserted pairs = size of the pairCoutns-map.
		 */
		inline unsigned int getSize()
		{
			return pairCounts.size();
		}

		/**
		 * sets the map-iterator to the begin of the pairCount-map.
		 */
		inline void begin()
		{
			it = pairCounts.begin();
		}

		/**
		 * sets the map-iterator to the next position.
		 */
		inline void next()
		{
			it++;
		}

		/**
		 * checks whether the map-iterator is at the end of the pairCount-map.
		 *
		 * \return true if the map iterator is at the end, false otherwise.
		 */
		inline bool isEnd()
		{
			return it == pairCounts.end();
		}

		/**
		 * gets the current pair at the map-iterators position.
		 *
		 * \return the pair at the map-iterators position.
		 */
		inline pair<unsigned int, unsigned int> current()
		{
			return it->first;
		}
};
#endif

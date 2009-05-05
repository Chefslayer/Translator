#ifndef __PAIRCOUNT_H__
#define __PAIRCOUNT_H__

#include <map>

class PairCount
{
	private:
		map<pair<unsigned int, unsigned int>, unsigned int> pairCounts;
		map<pair<unsigned int, unsigned int>, unsigned int> ::iterator it;
	public:
		inline void insert(pair<unsigned int, unsigned int> wordpair)
		{
			pairCounts[wordpair]++;
		}
		inline unsigned int getFreq(pair<unsigned int, unsigned int> wordpair)
		{
			return (pairCounts.find(wordpair))->second;
		}
		inline unsigned int getSize()
		{
			return pairCounts.size();
		}
		inline void begin()
		{
			it = pairCounts.begin();
		}
		inline void next()
		{
			it++;
		}
		inline bool isEnd()
		{
			return it == pairCounts.end();
		}
		inline pair<unsigned int, unsigned int> current()
		{
			return it->first;
		}
};

#endif

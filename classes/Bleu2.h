#ifndef BLEU2_H
#define BLEU2_H

#include <limits>
#include <cmath>
#include <math.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
//#include "SentenceTranslator.h"


/*void convertHypothesisToVector(HRCPtr currentHypothesis, std::vector<int> &result)
{
	while(!currentHypothesis->isNullHypothesis())
	{
		if(currentHypothesis->isTranslation())
		{
			std::list<int> prefix;
			currentHypothesis->targetPhrase.getPrefix(prefix);
			for(std::list<int>::const_reverse_iterator it=prefix.rbegin(); it!=static_cast<std::list<int>::const_reverse_iterator>(prefix.rend()); ++it)
			{
				result.insert(result.begin(),*it);
			}
		} else {
			result.insert(result.begin(),std::numeric_limits<int>::max()); //fail value!
		}
		currentHypothesis = currentHypothesis->getFather();
	}
}

*/



class Bleu2
{
	public:
		Bleu2()
			: gramCount(0), gramCountMatch(0), hypothesisLength(0), referenceLength(0)
		{}
		
		/**
		 * \brief A not so elegant hack to determine which index an iterator of a vector has.
		 */
		template<typename Iterator>
		int getIteratorDistance(Iterator left, Iterator right)
		{
			return static_cast<int>(&(*right) - &(*left));	
		}
		
		/**
		 * \brief  Counts the number of the n-grams in the hypothesis. 
		 *		
		 *			n-Grams are a sequence of n words. nGramCount counts all n-grams in the sentence. If a word is counted,
		 *			it is not counted twice. 
		 *
		 * \param	vector<int> const &hypothesis   	vector of indices of the words from the hypothesis sentence
		 * \param   vector<int> const &reference		vector of indices of the words from the reference sentence
		 * \return	            count of n-grams of the reference sentence, found in the hypothesis sentence
		 *
		 */
		int nGramCount(unsigned int &n, std::vector< unsigned int> const &hypothesis, std::vector<unsigned int> const &reference) 
		{
			bool found=false;
			if(n>0 && hypothesis.size()>=n && reference.size()>=n)
			{
				int count=0;
				std::vector<bool> isCounted(hypothesis.size(), false);
				for(std::vector<unsigned int>::const_iterator it=reference.begin(); it!=reference.end()-n+1; ++it)
				{
					std::vector<unsigned int>::const_iterator current=hypothesis.begin();
					found = false;
					while(current!=hypothesis.end())
					{
						current = std::search(current, hypothesis.end(),it,it+n);
						if(current != hypothesis.end() && isCounted[getIteratorDistance(hypothesis.begin(),current)]==false)
						{
							found = true;
							break;
						}
						if(current != hypothesis.end())
						{
							current++;
						}
					}
					if(found)
					{
						isCounted[getIteratorDistance(hypothesis.begin(),current)] = true;
						++count;
					}
				}
				return count;
			}
			else
			{
				return 0;
			}
		}
		
		/**
		 * \brief  Calculates the precision of a hypothesis ((n-grams of hypotheses)/(n-grams of reverences)). 
		 *
		 * \return	            the precision of all the n-grams of the reference sentence and the n-grams found in the hypothesis sentence
		 *
		 */
		double precision(unsigned int i) 
		{
			return static_cast<double>(gramCountMatch.at(i))/gramCount.at(i);
		}
		
		/**
		 * \brief  Calculates the Brevalty Penalty (BP). 
		 *
		 * \return	            the value of the BP
		 *
		 */
		double brevityPenalty() 
		{
			int c = hypothesisLength;
			int r = referenceLength;
			if(c>r)
			{
				return 1;
			}
			else
			{
				return exp(1-(static_cast<double>(r)/c));
			}
		}
		
		/**
		 * \brief Calculates the BLEU of all hypotheses. 
		 *
		 * \return	the bleu value of all the sentences.
		 *
		 */
		double bleu2(unsigned int n) 
		{
			double current=0;
			n = std::min<size_t>(n, referenceLength);
			n = std::min<size_t>(n, hypothesisLength);
			for(unsigned int i=1; i<=n; ++i)
			{
				double thePrecision = precision(i);
				if(thePrecision >= numeric_limits<double>::min()) //if(thePrecision!=0)
				{
					//std::cout << "thePrecision " << thePrecision<<std::endl;
					current += (1.0/n)*log(thePrecision);
					//std::cout << current << std::endl;
				}
				else
				{
					//std::cout << "thePrecision " << thePrecision<<std::endl;
					current += 0;
					//was:
					//current += -std::numeric_limits<double>::max();
				}
			}
			return (double)(brevityPenalty()*exp(current));
		}
		
/*		void addSentence(unsigned int n, std::vector<unsigned int> &buffer, std::vector<unsigned int> const &reference)
		{
			//std::vector<int> buffer;
			//convertHypothesisToVector(hypothesis, buffer);
			addSentence(n, buffer, reference);
		}
*/

		void addSentence(unsigned int n, std::vector<unsigned int> const &hypothesis, std::vector<unsigned int> const &reference)
		{
			if(gramCount.size()<n+1)
			{
				gramCount.resize(n+1);
				gramCountMatch.resize(n+1);
			}
			for(unsigned int i=1; i<=n; ++i){
				if(n<=reference.size())
				{
					gramCount.at(i) += reference.size()-i+1;
				}
				gramCountMatch.at(i) += nGramCount(i,hypothesis,reference);
				//std::cout << nGramCount(i,hypothesis,reference) << "/" << reference.size()-i+1 << " ";
			}
			//std::cout << std::endl;
			hypothesisLength += hypothesis.size();
			referenceLength += reference.size();
		}
		 void print()
		 {
		 	for(unsigned int i=1; i<=4; ++i){
		 		//std::cout << "\nBLUB: " << gramCount.at(i) << " " << gramCountMatch.at(i) << " " << hypothesisLength << " " << referenceLength << std::endl;
		 	}
		 }
	
	private:
		std::vector<unsigned int> gramCount;
		std::vector<unsigned int> gramCountMatch;
		unsigned int hypothesisLength;
		unsigned int referenceLength;
};

#endif

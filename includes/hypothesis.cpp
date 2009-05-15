#include <vector>
#include "hypothesis.h"

using namespace std;

/**
* inits a new Hypothesis with given values
* costs will be added to the p->costs and p->totalCosts
*
* \param p reference to the previous Hypothesis in a translation-process
* \param c costs for this Hypothesis
* \param t word in the target lang / translation
*/
Hypothesis::Hypothesis(Hypothesis *p , double c, unsigned int t)
{
	prevHyp = p;
	if (p!=NULL)
	{
		costs = p->costs;
		totalCosts = p->totalCosts;
	}
	else
	{
		totalCosts = 0;
	}
	costs.push_back(c);
	totalCosts += c;
	trans = t;
}

/**
* compares two Hpothesis by totalCosts
*
* \param i reference to a Hypothesis
* \param j reference to a Hypothesis
* \return compare result
*/
bool cmp_Hyp(Hypothesis* i, Hypothesis* j)
{
	return (i->totalCosts < j->totalCosts);
}

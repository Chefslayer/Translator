#include <vector>
#include "hypothesis.h"

using namespace std;

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

bool cmp_Hyp(Hypothesis* i, Hypothesis* j)
{
	return (i->totalCosts < j->totalCosts);
}

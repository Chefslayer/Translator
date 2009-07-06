#include <vector>
#include "hypothesis.h"

using namespace std;

Hypothesis::Hypothesis(Hypothesis *p ,double fCost, double eCost, unsigned int t)
{
	prevHyp = p;
	if (p!=NULL)
	{
		costs.push_back(p->costs[0]+fCost);
		costs.push_back(p->costs[1]+eCost);
	}
	else
	{
		costs.push_back(fCost);
		costs.push_back(eCost);
	}
	trans = t;
}

Hypothesis::Hypothesis(Hypothesis *p ,double fCost, double eCost, vector<unsigned int> &t)
{
	prevHyp = p;
	if (p!=NULL)
	{
		costs.push_back(p->costs[0]+fCost);
		costs.push_back(p->costs[1]+eCost);
	}
	else
	{
		costs.push_back(fCost);
		costs.push_back(eCost);
	}
	phraseTrans = t;
}

bool cmp_Hyp(Hypothesis* i, Hypothesis* j)
{
	return (i->costs[0] < j->costs[0]);
}

#include <vector>
#include "hypothesis.h"
#include <iostream>
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
	costs.resize(2);
	costs[0] = p==NULL? fCost : p->costs[0]+fCost;
	costs[1] = p==NULL? eCost : p->costs[1]+eCost;

	phraseTrans = t;
}

bool cmp_Hyp(Hypothesis* i, Hypothesis* j)
{
	double ic = 0.5*i->costs[0] + 0.5*i->costs[1];
	double jc = 0.5*j->costs[0] + 0.5*j->costs[1];
	return (ic<jc);
}

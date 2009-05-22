#ifndef HYPOTHESIS_H
#define HYPOTHESIS_H

#include <vector>

using namespace std;

struct Hypothesis
{
	Hypothesis *prevHyp;
	vector<double> costs;
	unsigned int trans;
	Hypothesis(Hypothesis *p,double fCost, double eCost, unsigned int t);
};

bool cmp_Hyp(Hypothesis* i, Hypothesis* j);

#endif //HYPOTHESIS_H //

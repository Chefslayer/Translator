#ifndef HYPOTHESIS_H
#define HYPOTHESIS_H

#include <vector>

using namespace std;

struct Hypothesis
{
	Hypothesis *prevHyp;
	vector<double> costs;
	double totalCosts;
	unsigned int trans;
	Hypothesis(Hypothesis *p, double c, unsigned int t);
};

bool cmp_Hyp(Hypothesis* i, Hypothesis* j);

#endif //HYPOTHESIS_H //

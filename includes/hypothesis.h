#ifndef HYPOTHESIS_H
#define HYPOTHESIS_H

#include <vector>

using namespace std;

struct Hypothesis
{
	vector<double> costs;
	Hypothesis *prevHyp;
	Hypothesis *prevTrans;
	Hypothesis(unsigned int cost);
};
#endif //HYPOTHESIS_H //

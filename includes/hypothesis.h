#ifndef HYPOTHESIS_H
#define HYPOTHESIS_H

#include <vector>

using namespace std;

struct Hypothesis
{
	vector<double> costs;
	Hypothesis *prevHyp;
	unsigned int prevTrans; //bin mir immer noch nicht sicher was mit letzter übersetzung gemeint ist…
	Hypothesis(unsigned int cost, unsigned int translation);
};
#endif //HYPOTHESIS_H //

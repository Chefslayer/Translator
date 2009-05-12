#ifndef HYPOTHESIS_H
#define HYPOTHESIS_H

//include <vector>

using namespace std;

struct Hypothesis
{
	double costs;
	Hypothesis *prevHyp;
	unsigned int prevTrans; //bin mir immer noch nicht sicher was mit letzter übersetzung gemeint ist…
	Hypothesis(Hypothesis *_prevHyp, double _costs, unsigned int _prevTrans);
};
#endif //HYPOTHESIS_H //

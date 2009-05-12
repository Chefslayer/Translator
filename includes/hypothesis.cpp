#include <vector>
#include "hypothesis.h"

using namespace std;

Hypothesis::Hypothesis(unsigned int cost,unsigned int translation)
{
	costs.push_back(cost);
	prevHyp = NULL;
	prevTrans = translation;
}


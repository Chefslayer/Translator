#include <vector>
#include "hypothesis.h"
using namespace std;

Hypothesis::Hypothesis(unsigned int cost)
{
	costs.push_back(cost);
	prevHyp = NULL;
	prevTrans = NULL;
}


#include <vector>
#include "hypothesis.h"

using namespace std;

Hypothesis::Hypothesis(Hypothesis *_prevHyp, double _costs,unsigned int _prevTrans)
{
	costs = _costs;
	prevHyp = _prevHyp ;
	prevTrans = _prevTrans;
}


#include <vector>
#include "hypothesis.h"

using namespace std;

Hypothesis::Hypothesis(Hypothesis *_prevHyp, double _costs,unsigned int _trans)
{
	costs = _costs;
	prevHyp = _prevHyp ;
	trans = _trans;
}


#include "PhrasePair.h"
#include <vector>

using namespace std;

PhrasePair::PhrasePair(vector<unsigned int> &s, vector<unsigned int> &t)
{
	this->src = s;
	this->target = t;
}

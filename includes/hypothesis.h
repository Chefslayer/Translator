/**
 * @file
 * @author  Gruppe 2
 * @version 1.0
 *
 * @section DESCRIPTION
 *
 * This file defines the Hypothesis struct and a compare-function for it.
 */

#ifndef HYPOTHESIS_H
#define HYPOTHESIS_H

#include <vector>

using namespace std;

/**
* inits a new Hypothesis with given values.
*
* \param p reference to the previous Hypothesis in a translation-process
* \param c costs for this Hypothesis
* \param t word in the target lang / translation
*/
struct Hypothesis
{
	Hypothesis *prevHyp;
	vector<double> costs;
	unsigned int trans;
	Hypothesis(Hypothesis *p,double fCost, double eCost, unsigned int t);
};

/**
* compares two Hpothesis by totalCosts
*
* \param i reference to a Hypothesis
* \param j reference to a Hypothesis
* \return compare result
*/
bool cmp_Hyp(Hypothesis* i, Hypothesis* j);

#endif

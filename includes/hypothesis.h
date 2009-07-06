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
 * The Hypothesis struct holds costs for a specific hypothesis for a word and a pointer to another Hypothesis, so that we're able to build a tree of hypos and to calculate a best one.
 */
struct Hypothesis
{
	/// pointer to the previous Hypothesis (which is in the last stack).
	Hypothesis *prevHyp;

	/// holds all costs to get to this hypothesis, costs[0] accumulates the fCosts and costs[1] the eCosts.
	vector<double> costs;

	/// holds the code for the word that this hypothesis is for.
	unsigned int trans;
	vector<unsigned int> phraseTrans;
	
	/**
	 * inits a new Hypothesis with given values.
	 *
	 * \param p reference to the previous Hypothesis in a translation-process
	 * \param c costs for this Hypothesis
	 * \param t word in the target lang / translation
	 */
	Hypothesis(Hypothesis *p,double fCost, double eCost, unsigned int t);

	/**
	 * inits a new Hypothesis with given values.
	 *
	 * \param p reference to the previous Hypothesis in a translation-process
	 * \param c costs for this Hypothesis
	 * \param t vector of words in the target lang / translation
	 */
	Hypothesis(Hypothesis *p,double fCost, double eCost, vector<unsigned int> &t);	
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

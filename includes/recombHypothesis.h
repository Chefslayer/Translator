/**
 * @file
 * @author  Gruppe 2
 * @version 1.0
 *
 * @section DESCRIPTION
 *
 * This file defines the recombined Hypothesis struct.
 */

#ifndef RECOMBHYPOTHESIS_H
#define RECOMBHYPOTHESIS_H

#include <vector>

using namespace std;

struct recombHypothesis;

struct recombHypothesisEntry
{
	/// holds the costs for this translation of a phrase.
	double costs;

	/// holds the translation codes for the phrase that this hypothesis is for.
	vector<unsigned int> trans;

	/// pointer to the previous recombHypothesis.
	recombHypothesis* prev;
};

/*
 *The Hypothesis struct holds costs for a specific hypothesis for a word and a pointer to another Hypothesis, so that we're able to build a tree of hypos and to calculate a best one.
 */
struct recombHypothesis
{
	/// all possible translations
	vector<recombHypothesisEntry*> entries;

	/// index of the best Hypo in the entries vector
	unsigned int bestEntry;

	/// holds the costs to get to this hypothesis.
	double costs;
};
#endif

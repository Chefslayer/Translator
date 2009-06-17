/**
 * @file
 * @author  Gruppe 2
 * @version 1.0
 *
 * @section DESCRIPTION
 *
 * This file defines functions for outputting some information on the standard output during a traning of the translator.
 */

#ifndef __OUTPUT_H__
#define __OUTPUT_H__

#include <string>
#include <vector>
#include <utility>
#include "../classes/PairCount.h"
#include "../classes/SingleCount.h"
#include "../classes/Lexicon.h"
#include "../classes/Tree.cpp"

using namespace std;


/**
 * displays the Freqs on the cout
 *
 * \param pairs the pairs-object
 * \param singlesF singles-object for source lang
 * \param singlesE singles-object for target lang
 * \param f lexicon to look up the words of the source lang
 * \param e lexicon to look up the words of the target lang
 */

void showFreqPhrases_subTrees_rek(Node<unsigned int> *current, vector<unsigned int> v_f, vector<unsigned int> v_e, const string &s_f, string s_e, Tree<unsigned int> *phrasesF, Tree<unsigned int> *phrasesE, Lexicon &e);

void showFreqPhrases_subTrees(string s_f, vector<unsigned int> v_f, Tree<unsigned int> *t, Tree<unsigned int> *phrasesF, Tree<unsigned int> *phrasesE, Lexicon &e);

void showFreqPhrases_rek(Node<NodeOfTrees*>* current, string s_f, vector<unsigned int> v_f, Tree<unsigned int> *phrasesF, Tree<unsigned int> *phrasesE, Lexicon &f, Lexicon &e);

/**
 * displays the Freqs for pairs on the cout
 *
 * ...
 */
void showFreqPhrases(Tree<NodeOfTrees*> *phrasePairs, Tree<unsigned int> *phrasesF, Tree<unsigned int> *phrasesE, Lexicon &f, Lexicon &e);

#endif

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
#include "../classes/Tree.h"
#include "../classes/TreeOfTrees.h"

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
void showFreq(PairCount& pairs, SingleCount& singlesF, SingleCount& singlesE, Lexicon& f, Lexicon& e);
/**
 * this function cacls the frequency for a possible translation.
 *
 * \param current current node
 * \param v_f vector with the words of the current phrase in source lang
 * \param v_e vector with the words of the current phrase in target lang
 * \param s_f string with the words of the current phrase in source lang
 * \param s_e string with the words of the current phrase in target lang
 * \param phrasesF tree of the src-lang phrases
 * \param phrasesE tree of the target-lang phrases
 * \param e Lexicon for the target lang
 */
//void showFreqPhrases_subTrees_rek(Node<unsigned int> *current, vector<unsigned int> v_f, vector<unsigned int> v_e, const string &s_f, string s_e, Tree<unsigned int> *phrasesF, Tree<unsigned int> *phrasesE, Lexicon &e);

/**
 * starts the recursive calculation of possible translations for a phrase and its frequency.
 *
 * \param s_f string with the words of the current phrase in source lang
 * \param v_f vector with the words of the current phrase in source lang
 * \param t sub-tree holding all possible translations for a phrase in src-lang
 * \param phrasesF tree of the src-lang phrases
 * \param phrasesE tree of the target-lang phrases
 * \param e Lexicon for the target lang
 */
//void showFreqPhrases_subTrees(string s_f, vector<unsigned int> v_f, Tree<unsigned int> *t, Tree<unsigned int> *phrasesF, Tree<unsigned int> *phrasesE, Lexicon &e);

/**
 * concatinates the phrases of the src lang, and calls a function to display all possible translations for this phrase.
 *
 * \param current current phrase in src-lang
 * \param s_f string with the words of the current phrase in source lang
 * \param v_f vector with the words of the current phrase in source lang
 * \param phrasesF tree of the src-lang phrases
 * \param phrasesE tree of the target-lang phrases
 * \param f Lexicon for the source lang
 * \param e Lexicon for the target lang
 */
//void showFreqPhrases_rek(Node<NodeOfTrees*>* current, string s_f, vector<unsigned int> v_f, Tree<unsigned int> *phrasesF, Tree<unsigned int> *phrasesE, Lexicon &f, Lexicon &e);

/**
 * starts the recursiv concatination of phrases in the src lang.
 *
 * \param phrasePairs main tree-of-trees with all possible translations of phrases
 * \param phrasesF tree of the src-lang phrases
 * \param phrasesE tree of the target-lang phrases
 * \param f Lexicon for the source lang
 * \param e Lexicon for the target lang
 */
//void showFreqPhrases(Tree<NodeOfTrees*> *phrasePairs, Tree<unsigned int> *phrasesF, Tree<unsigned int> *phrasesE, Lexicon &f, Lexicon &e);

#endif

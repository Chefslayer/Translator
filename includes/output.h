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

#endif

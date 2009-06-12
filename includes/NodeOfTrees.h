/**
 * @file
 * @author  Gruppe 2
 * @version 1.0
 *
 * @section DESCRIPTION
 *
 * This struct defines a data-type for prefix-trees of prefix-trees.
 */

#ifndef NODEOFTREES_H
#define NODEOFTREES_H

#include <vector>
#include "../classes/Tree.h"

using namespace std;

/**
 * This struct defines a data-type for prefix-trees of prefix-trees.
 */
struct NodeOfTrees
{
	// a word of a phrase
	unsigned int word;

	/// sub-tree
	Tree<unsigned int>* tree;

	/**
	 * inits a new node with given values.
	 *
	 * \param word the word of a phrase
	 * \param tree a sub-tree
	 */
	NodeOfTrees(unsigned int word, Tree<unsigned int>* tree);

	/**
	 * Operator to compare two NodeOfTrees (comparing by word).
	 *
	 * \param n the NodeOfTrees to compare the current one with
	 * \return 1 if the words are equal, 0 otherwise
	 */
	bool operator==(NodeOfTrees n) const;
};

#endif

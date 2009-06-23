/**
 * @file
 * @author  Gruppe 2
 * @version 1.0
 *
 * @section DESCRIPTION
 *
 * This file implements the Tree and the Nodes Classes for a prefix-tree.
 */

#ifndef __TREEOFTREES_H__
#define __TREEOFTREES_H__

#include "TreeOfTrees.h"
#include <vector>
#include "../includes/PhrasePair.h"
#include "../includes/NodeOfTrees.h"
#include <iostream>

using namespace std;

/**
 * The Tree class implements a prefix-tree to count phrases of word-hypothesis.
 */
class TreeOfTrees
{
	public:

		NodeOfTrees* root;

		/** inits a new Tree.
		 *
		 * \param the root-node
		 */
		TreeOfTrees(NodeOfTrees* root);

		/** inserts a vector of words in the tree.
		 *
		 * \param values a vector of unsigned int-values which are inserted
		 * \return reference to the node with the last value
		 */
		NodeOfTrees* insert(vector<unsigned int>& values);

		/** inserts a phrasePair in the tree of prefixtrees and counts the occurrences of it.
		 *
		 * \param p src-target-phrase pair
		 */
		void insert(PhrasePair* p);

		/** gets the count for a phrase of words (unsigned ints)
		 *
		 * \param phrase vector with the word-cods of the phrase
		 */
//		unsigned int getCount(vector<unsigned int> &phrase);
};
#endif

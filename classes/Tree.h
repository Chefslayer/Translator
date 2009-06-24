/**
 * @file
 * @author  Gruppe 2
 * @version 1.0
 *
 * @section DESCRIPTION
 *
 * This file implements the Tree and the Nodes Classes for a prefix-tree.
 */

#ifndef __TREE_H__
#define __TREE_H__

#include <vector>
#include <set>
#include "../includes/Node.h"

using namespace std;

/**
 * The Tree class implements a prefix-tree to count phrases of word-hypothesis.
 */
class Tree
{
	public:

		Node* root;

		/** inits a new Tree.
		 *
		 * \param the root-node
		 */
		Tree(Node* root);

		/** inserts a vector of words in the tree.
		 *
		 * \param values a vector of unsigned int-values which are inserted
		 * \return reference to the node with the last value
		 */
		Node* insert(vector<unsigned int> &values);

		/** gets the count for a phrase of words (unsigned ints)
		 *
		 * \param phrase vector with the word-cods of the phrase
		 */
		unsigned int getCount(vector<unsigned int> &phrase);
};
#endif

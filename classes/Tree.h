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

using namespace std;

/**
 * The Node class implements the nodes for a prefix-tree to count phrases of word-hypothesis.
 */
class Node
{
	public:
		/// all child Nodes
		vector<Node*>childNodes;

		/// the count for this word
		unsigned int count = 0;

		/// the word of a phrase
		unsigned int word = 0;

		/// Constructor to create a new Node
		Node(unsigned int word);
};

/**
 * The Tree class implements a prefix-tree to count phrases of word-hypothesis.
 */
class Tree
{
	private:
		/// the root-node of the tree
		Node* root = NULL;
	public:
		/// inits a new Tree
		Tree();
};
#endif

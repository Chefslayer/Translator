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
#include "../includes/PhrasePair.h"

using namespace std;

/**
 * The Node class implements the nodes for a prefix-tree to count phrases of word-hypothesis.
 */
template <class T> class Node
{
	public:
		/// all child Nodes
		vector<Node<T>* > childNodes;

		/// the count for this word
		unsigned int count;

		/// the word of a phrase (unsigned int) or a prefix-tree (NodeOfTrees)
		T value;

		/// Constructor to create a new Node
		Node(T value);

		/** searches if a childNode with a given value exists
		 *
		 * \throws bool nodeDoesNotOccur - no node with the given value exists yet
		 * \param value the value to search for
		 * \return the position in the childNodes-vector where the value occurs
		 */
		unsigned int hasChildNode(T value);

		/** checks if a childNode with the given value exists, maybe creates a new one and increments its count
		 *
		 * \exception bool catches the nodeDoesNotOccur thrown by hasChildNode()
		 * \param value to insert/count
		 * \return the node with the value
		 */
		Node<T>* insertChildNode(T value);
};

/**
 * The Tree class implements a prefix-tree to count phrases of word-hypothesis.
 */
template <class T> class Tree
{
	private:
		/// the root-node of the tree
		Node<T>* root;

	public:
		/** inits a new Tree and creates the root node with the given value.
		 *
		 * \param value the root-value
		 */
		Tree(T value);

		/** gets the root Node.
		 *
		 * \param return the root Node
		 */
		Node<T>* getRoot();

		/** inserts a vector of T-values in the tree.
		 *
		 * \param values a vector of T-values which are inserted
		 * \return reference to the node with the last value
		 */
		Node<T>* insert(vector<T> &values);

		/** inserts a phrasePair in the tree of prefixtrees and counts the occurrences of it.
		 *
		 * \param p src-target-phrase pair
		 */
		void insert(PhrasePair* p);

		/** gets the count for a phrase of words (unsigned ints)
		 *
		 * \param phrase vector with the word-cods of the phrase
		 */
		unsigned int getCount(vector<T> &phrase);
};
#endif

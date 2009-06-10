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
		vector<Node<T>*> childNodes;

		/// the count for this word
		unsigned int count;

		/// the word of a phrase or a prefix-tree
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

		/// for trees of trees you can define if this tree is the root tree, initialized with 0
		bool rootNode;
	public:
		/** inits a new Tree and creates the root node with the given value
		 *
		 * \param value the root-value
		 */
		Tree(T value);

		/** sets the rootNode attribute to the given value
		 *
		 * \param val the value which the rootNode attribute is setted to
		 */
		void isRootOfAnOtherTree(bool val);

		/** gets the value of the rootNode attribute
		 *
		 * \param return the value of the rootNode attribute
		 */
		bool isRootOfAnOtherTree();

		/** gets the root Node
		 *
		 * \param return the root Node
		 */
		Node<T>* getRoot();

		/** inserts a vector of words in the tree
		 *
		 * \param words a vector of words that are inserted
		 */
		void insert(vector<unsigned int> &words);

		/** inserts a phrasePair in the tree of prefixtrees and counts the occurrences of it
		 *
		 * \param p src-target-phrase pair
		 */
		void insert(PhrasePair* p);
};
#endif

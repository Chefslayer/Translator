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

//#include <vector>
#include <set>
#include "../includes/PhrasePair.h"

using namespace std;

template<typename T, class Comp = std::less<T> > struct ptr_comp
{
	bool operator()( T const* const lhs, T const* const rhs ) const
	{
		return comp( *lhs, *rhs );
	}
	private:
		Comp comp;
};

/**
 * The Node class implements the nodes for a prefix-tree to count phrases of word-hypothesis.
 */
template <class T> class Node
{
	public:
		/// all child Nodes
		//vector<Node<T>* > childNodes;
		set< Node<T>*, ptr_comp<Node<T> > > childNodes;

		/// the count for this word
		unsigned int count;

		/// the word of a phrase (unsigned int) or a prefix-tree (NodeOfTrees)
		T value;

		/// Constructor to create a new Node
		Node(T value);

		/**
		 * Operator to compare two Nodes (comparing by value).
		 *
		 * \param n the Node to compare the current one with
		 * \return 1 if the value of the current is smaller than the param-node-value
		 */
		bool operator<(const Node<T>& node) const;
};

/**
 * The Tree class implements a prefix-tree to count phrases of word-hypothesis.
 */
template <class T> class Tree
{
	private:
		// the root-node of the tree
		//Node<T>* root;

	public:

		Node<T>* root;

		/** inits a new Tree and creates the root node with the given value.
		 *
		 * \param value the root-value
		 */
		Tree(T value);

		/** inserts a vector of T-values in the tree.
		 *
		 * \param values a vector of T-values which are inserted
		 * \return reference to the node with the last value
		 */
		void insert(vector<T> &values);

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

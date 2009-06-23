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

#include <set>
#include <vector>
#include "../classes/Tree.h"

using namespace std;


template<typename T, class Comp = std::less<T> > struct ptr_ptr_comp
{
	bool operator()( T const* const lhs, T const* const rhs ) const
	{
		return comp( *lhs, *rhs );
	}
	private:
		Comp comp;
};


/**
 * This struct defines a data-type for prefix-trees of prefix-trees.
 */
struct NodeOfTrees
{
	/// all childNodes
	set<NodeOfTrees*, ptr_ptr_comp<NodeOfTrees> > childNodes;

	/// the count for this word
	unsigned int count;

	/// a word of a phrase
	unsigned int word;

	/// sub-tree
	Tree* tree;

	/**
	 * inits a new node with given values.
	 *
	 * \param word the word of a phrase
	 * \param tree a sub-tree
	 */
	NodeOfTrees(unsigned int word, Tree* tree);

	/**
	 * Operator to compare two NodeOfTrees (comparing by word).
	 *
	 * \param n the NodeOfTrees to compare the current one with
	 * \return 1 if the words are equal, 0 otherwise
	 */
	bool operator==(const NodeOfTrees& n) const;

	/**
	 * Operator to compare two NodeOfTrees (comparing by word).
	 *
	 * \param n the NodeOfTrees to compare the current one with
	 * \return 1 if the word of the current is smaller than the n-word
	 */
	bool operator<(const NodeOfTrees& n) const;
};

#endif

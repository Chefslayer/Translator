/**
 * @file
 * @author  Gruppe 2
 * @version 1.0
 *
 * @section DESCRIPTION
 *
 * This struct defines a data-type for unsigned-int-prefix-trees.
 */

#ifndef NODE_H
#define NODE_H

#include <set>

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
 * The Node struct implements the nodes for a prefix-tree to count phrases of word-hypothesis.
 */
struct Node
{
	public:
		/// all child Nodes
		set<Node*, ptr_comp<Node> > childNodes;

		/// the count for this word
		unsigned int count;

		/// the word of a phrase (unsigned int) or a prefix-tree (NodeOfTrees)
		unsigned word;

		/// Constructor to create a new Node
		Node(unsigned int word);

		/**
		 * Operator to compare two Nodes (comparing by word).
		 *
		 * \param n the Node to compare the current one with
		 * \return 1 if the word of the current is smaller than the param-node-word
		 */
		bool operator<(const Node& node) const;
		
};

#endif

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

using namespace std;

/**
 * This struct defines a data-type for prefix-trees of prefix-trees.
 */
struct NodeOfTrees
{
	unsigned int word;
	Tree<unsigned int> tree;
	NodeOfTrees(unsigned int word, Tree<unsigned int> tree);
};
#endif

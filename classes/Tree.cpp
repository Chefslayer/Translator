/**
 * @file
 * @author Gruppe 2
 * @version 1.0
 *
 * @section DESCRIPTION
 *
 *This file implements the Tree and the Nodes Classen for a prefix-tree.
 */

#ifndef __TREE_CPP__
#define __TREE_CPP__

#include "Tree.h"
#include <vector>
#include <set>
#include "../includes/Node.h"
#include <iostream>

using namespace std;

Tree::Tree(Node* root)
{
	this->root = root;
}

/**
 * inserts a sentence(vector of words) into the Tree
 * \param values a vector of unsigned int-values (sentence) to insert
 * \return a pointer to the node with the last value
 */

Node* Tree::insert(vector<unsigned int> &values)
{
	
	if (values.size() == 0)
		return root;

	Node *node = root;
	for (vector<unsigned int>::iterator it=values.begin(); it != values.end(); it++)
	{
		pair<set<Node*>::iterator, bool> temp = node->childNodes.insert(new Node(*it));
		node = *(temp.first);
	}
	node->count++;
	return node;
}

/**
 * finds the number of appearance of a given phrase (unsigned int vector)
 * \param phrase vector to search for
 * \return count the number of appearance of the given phrase
 */
unsigned int Tree::getCount(vector<unsigned int> &phrase)
{
	Node *node = root;
	set<Node*>::iterator tmp;
	
	for (vector<unsigned int>::iterator it=phrase.begin(); it != phrase.end(); it++)
	{
		if ((tmp = (node->childNodes.find(new Node(*it)))) == (node->childNodes.end()))
			return 0;
		node = *node->childNodes.find(new Node(*it));
	}
	return (node->count);
}

#endif

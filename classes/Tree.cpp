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

#ifndef __TREE_CPP__
#define __TREE_CPP__

#include "Tree.h"
#include <string>
#include <vector>
#include "../includes/PhrasePair.h"
#include "../includes/NodeOfTrees.h"
#include <typeinfo>
#include <set>
#include <utility>
#include <iostream>

using namespace std;

template <class T> bool Node<T>::operator<(const Node<T>& node) const
{
	return value < node.value;
}

template <class T> Tree<T>::Tree(T value)
{
	  root = new Node<T>(value);
}

template <class T> Node<T>::Node(T value)
{
	this->value = value;
	this->count = 1;
}

template <class T> void Tree<T>::insert(vector<T> &values)
{
	//cout << "insert" << endl;
	if (values.size()== 0)
		return;

	Node<T> *node = root;
	for (typename vector<T>::iterator it=values.begin(); it != values.end();it++)
	{
//		pair<Node<unsigned int>*::iterator, bool> temp = node->childNodes.insert(new Node<T>(*it));
//		cout << node->childNodes.insert(new Node<T>(*it)).second << endl;
		//node = *(temp.first);
		node = *(node->childNodes.insert(new Node<T>(*it)).first);
	}
}


template <class T> void Tree<T>::insert(PhrasePair* p)
{

}

template <class T> unsigned int Tree<T>::getCount(vector<T> &phrase)
{
	return 5;
}
#endif

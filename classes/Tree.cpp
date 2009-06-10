#include "Tree.h"
#include <vector>

using namespace std;

template <class T> Node<T>::Node(T value)
{
	this->value = value;
	this->count = 1;
}

template <class T> unsigned int Node<T>::hasChildNode(T value)
{
	for (unsigned int i=0; i<childNodes.size(); i++)
	{
		if (childNodes[i]->value == value)
			return i;
	}
	// we did not found a node with the given value -> throw nodeDoesNotOccur exception
	throw (bool)1;
}

template <class T> Node<T>* Node<T>::insertChildNode(T value)
{
	unsigned int pos;
	// search if a Node with the word already exists in childNodes (if there is one -> get its position)
	try 
	{
		pos = this->hasChildNode(value);
	}
	catch (bool nodeDoesNotOccur)
	{
		// node does not exist yet -> create it and return the new node
		childNodes.push_back(new Node<T>(value));
		return childNodes[childNodes.size()-1];
	}
	// node with the given value already exists -> increment count and return the node
	childNodes[pos]->count++;
	return childNodes[pos];
}

template <class T> Tree<T>::Tree(T value)
{
	root = new Node<T>(value);
}

template <class T> void Tree<T>::isRootOfAnOtherTree(bool val)
{
	rootNode = val;
}

template <class T> bool Tree<T>::isRootOfAnOtherTree()
{
	return rootNode;
}

template <class T> Node<T>* Tree<T>::getRoot()
{
	return root;
}

template <class T> void Tree<T>::insert(vector<unsigned int> &words)
{
	Node<unsigned int>* n = root;
	for (unsigned int i=0; i<words.size(); i++)
	{
		n = n->insertChildNode(words[i]);
	}
}

template <class T> void Tree<T>::insert(PhrasePair* p)
{
	// TODO
}

#include "Tree.h"
#include <string>
#include <vector>
#include "../includes/PhrasePair.h"
#include "../includes/NodeOfTrees.h"
#include <typeinfo> 

using namespace std;

template <class T> Node<T>::Node(T value)
{
	this->value = value;
	this->count = 1;
}

template <class T> unsigned int Node<T>::hasChildNode(T value)
{
	// check T, caus for T = NodeOfTrees* we don't want to compare the pointers, but the objects
	if ( (string)typeid(value).name() == "P11NodeOfTrees")
	{
		for (unsigned int i=0; i<childNodes.size(); i++)
		{
			if (*(NodeOfTrees*)childNodes[i]->value == *(NodeOfTrees*)value)
				return i;
		}
	}
	else
	{
		for (unsigned int i=0; i<childNodes.size(); i++)
		{
			 if (childNodes[i]->value == value)
				return i;
		}
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

template <class T> Node<T>* Tree<T>::getRoot()
{
	return root;
}

template <class T> Node<T>* Tree<T>::insert(vector<T> &values)
{
	Node<T>* n = root;
	for (unsigned int i=0; i<values.size(); i++)
	{
		n = n->insertChildNode(values[i]);
	}
	return n;
}

template <class T> void Tree<T>::insert(PhrasePair* p)
{
	// transform src-words into src-NodeOfTrees
	vector<NodeOfTrees*> src;
	src.resize(p->src.size());
	for (unsigned int i=0; i<p->src.size(); i++)
	{
		src[i] = new NodeOfTrees(p->src[i], new Tree<unsigned int>(0));
	}

	// insert/increment src-path
	Node<T>* lastNode = this->insert(src);

	// concat target-path to the src-paths-last-node
	lastNode->value->tree->insert(p->target);
}

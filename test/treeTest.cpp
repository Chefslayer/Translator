/**
 * @file
 * @author  Gruppe 2
 * @version 1.0
 *
 * @section DESCRIPTION
 *
 * Tests the Tree-class for phrase-trees and for trees of phrase-trees.
 */

#include <string>
#include <iostream>
#include <vector>
//#include "../classes/Tree.h"
#include "../classes/Tree.cpp"
#include "../includes/NodeOfTrees.h"
#include "../includes/PhrasePair.h"

using namespace std;

int main(int argc, char** argv)
{
	// create some test data
	vector<unsigned int> v;
	v.push_back(1);
	v.push_back(1);

	vector<unsigned int> w;
	w.push_back(1);
	w.push_back(0);

	PhrasePair* p = new PhrasePair(v,w);
	PhrasePair* p2 = new PhrasePair(v,v);

	// create the trees
	Tree<unsigned int> *t = new Tree<unsigned int>(0);
	Tree<NodeOfTrees*>* phrasePairs = new Tree<NodeOfTrees*>(new NodeOfTrees(0, NULL));

	// insert data for normal phrase-tree
	t->insert(p->src);
	t->insert(p->src);
	t->insert(p->target);

	// insert data for tree-of-trees
	phrasePairs->insert(p); // 11->10
	phrasePairs->insert(p2); // 11->11


	// check output	for the normal phrase-tree
	cout << "checking phrase-tree..." << endl;
	cout << "output: ";
									// output should be:
	cout << t->getRoot()->count;					// 1
	cout << t->getRoot()->childNodes[0]->count;			// 3
	cout << t->getRoot()->childNodes[0]->childNodes[0]->count;	// 2
	cout << t->getRoot()->childNodes[0]->childNodes[1]->count;	// 1
	cout << endl << endl;

	// check output for the tree-of-trees
	cout << "checking tree-of-trees..." << endl;
	cout << "output: ";
											// output should be:
	cout << phrasePairs->getRoot()->count;						// 1
	cout << phrasePairs->getRoot()->childNodes[0]->count;				// 2
	cout << phrasePairs->getRoot()->childNodes[0]->childNodes[0]->count;		// 2

	cout << phrasePairs->getRoot()->childNodes[0]->childNodes[0]->value->tree
			->getRoot()->count;						// 1

	cout << phrasePairs->getRoot()->childNodes[0]->childNodes[0]->value->tree
			->getRoot()->childNodes[0]->count;				// 2

	cout << phrasePairs->getRoot()->childNodes[0]->childNodes[0]->value->tree
			->getRoot()->childNodes[0]->childNodes[0]->count;		// 1

	cout << phrasePairs->getRoot()->childNodes[0]->childNodes[0]->value->tree
			->getRoot()->childNodes[0]->childNodes[1]->count;		// 1

	cout << endl;

	return 0; //EXIT_SUCCESS;
}

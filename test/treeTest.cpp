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
#include "../classes/Lexicon.h"
#include "../classes/Tree.h"
#include "../classes/TreeOfTrees.h"
#include "../includes/PhrasePair.h"
#include "../includes/output.h"

using namespace std;
static Lexicon f;
static Lexicon e;

int main(int argc, char** argv)
{
	// create some test data
	vector<unsigned int> v;
	v.push_back(1);
	v.push_back(3);

	vector<unsigned int> w;
	w.push_back(1);
	w.push_back(0);

	PhrasePair* p = new PhrasePair(v,w);
	PhrasePair* p2 = new PhrasePair(v,v);

	Tree* testT = new Tree(new Node(0));

	testT->insert(p->src);
	testT->insert(p->src);
	testT->insert(p->target);
	p->src.push_back(2);
	testT->insert(p->src);
	p->src.pop_back();

	cout << "c:" << testT->getCount(p->src)<<endl;

	cout << (*testT->root->childNodes.begin())->word<<endl;							// 1

/*


	.find(new Node(100));
	// create the trees
	Tree *t				= new Tree(new Node(100));
	t->root->childNodes.begin()

	Tree *phrasesF = new Tree(new Node(101));
	Tree *phrasesE = new Tree(new Node(102));

	TreeOfTrees* phrasePairs	= new TreeOfTrees(new NodeOfTrees(200, NULL));

	// check output	for the normal phrase-tree
	cout << "checking phrase-tree..." << endl;

	// insert data for normal phrase-tree
	t->insert(p->src);
	t->insert(p->src);
	t->insert(p->target);

	cout << "output: ";
														// output should be:
	cout << t->root->count <<",";										// 0
	cout << t->root->word <<endl;										// 100

	cout << (*t->root->childNodes.begin())->count<<",";							// 0
	cout << (*t->root->childNodes.begin())->word<<endl;							// 1

	cout << (*(*t->root->childNodes.begin())->childNodes.begin())->count<<",";				// 1
	cout << (*(*t->root->childNodes.begin())->childNodes.begin())->word<<endl;				// 0

	set<Node*>::iterator it = (*t->root->childNodes.begin())->childNodes.begin();
	it++;
	cout << (*it)->word << ",";										// 3
	cout << (*it)->count << endl;										// 2

	// check output for the tree-of-trees
	cout << "checking tree-of-trees..." << endl;

	// insert data for tree-of-trees
	phrasePairs->insert(p); // 13->10
	phrasePairs->insert(p2); // 13->13

	cout << "output: ";
	showFreqPhrases(phrasePairs, phrasesF, phrasesE, f, e);

/*
	cout << "output: ";
											// output should be:
	cout << phrasePairs->root->count << ",";					// 0
	cout << phrasePairs->root->word << endl;					// 200

	set<NodeOfTrees*>::iterator it2;

	it2 = phrasePairs->root->childNodes.begin();
	cout << (*it2)->count<<",";							// 0
	cout << (*it2)->word<<endl;							// 1

	it2 = (*it2)->childNodes.begin();
	cout << (*it2)->count<<",";							// 2
	cout << (*it2)->word<<endl;							// 3

	cout << (*it2)->tree->root->count << ",";					// 0
	cout << (*it2)->tree->root->word << endl;					// 0


	it = (*it2)->tree->root->childNodes.begin();
	cout << (*it)->count<<",";							// 0
	cout << (*it)->word<<endl;							// 1

	cout << "y"<<(*it)->childNodes.size() << endl;					// 2

	it = (*it)->childNodes.begin();
	cout << (*it)->count<<",";							// 1
	cout << (*it)->word<<endl;							// 0

	it++;
	cout << (*it)->count<<",";							// 1
	cout << (*it)->word<<endl;							// 3

	cout << endl;
*/
	return 0; //EXIT_SUCCESS;
}

#include "TreeOfTrees.h"
#include <vector>
#include "../includes/PhrasePair.h"
#include "../includes/NodeOfTrees.h"

using namespace std;

TreeOfTrees::TreeOfTrees(NodeOfTrees* root)
{
	this->root = root;
}

NodeOfTrees* TreeOfTrees::insert(vector<unsigned int>& values)
{
	if (values.size() == 0)
		return root;

	NodeOfTrees *node = root;
	for (vector<unsigned int>::iterator it=values.begin(); it != values.end(); it++)
	{
		pair<set<NodeOfTrees*>::iterator, bool> temp = node->childNodes.insert(new NodeOfTrees(*it, new Tree(new Node(0))));
		node = *(temp.first);
	}
	node->count++;
	return node;
}

void TreeOfTrees::insert(PhrasePair* p)
{
	// insert/increment src-path
	NodeOfTrees* lastNode = this->insert(p->src);

	// concat target-path to the src-paths-last-node
	lastNode->tree->insert(p->target);
}

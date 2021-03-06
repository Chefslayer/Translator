#include "NodeOfTrees.h"
#include "../classes/Tree.h"

using namespace std;

NodeOfTrees::NodeOfTrees(unsigned int word, Tree* tree)
{
	this->word = word;
	this->tree = tree;
	this->count = 0;
};

bool NodeOfTrees::operator==(const NodeOfTrees& n) const
{
	return word == n.word;
}

bool NodeOfTrees::operator<(const NodeOfTrees& n) const
{
	return word < n.word;
}

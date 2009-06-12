#include <vector>
#include "NodeOfTrees.h"
#include "../classes/Tree.h"

using namespace std;

NodeOfTrees::NodeOfTrees(unsigned int word, Tree<unsigned int>* tree)
{
	this->word = word;
	this->tree = tree;
};

bool NodeOfTrees::operator==(NodeOfTrees n) const
{
	return word == n.word;
}

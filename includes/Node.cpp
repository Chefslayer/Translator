#include "NodeOfTrees.h"

using namespace std;

Node::Node(unsigned int word)
{
	this->word = word;
	this->count = 0;
}

bool Node::operator<(const Node& node) const
{
	return word < node.word;
}

/**
 * @file
 * @author  Gruppe 2
 * @version 1.0
 *
 * @section DESCRIPTION
 *
 * Tests the NodeOfTrees-Struct and its compare-operator == .
 */

#include <string>
#include <iostream>
#include <map>
#include <vector>
#include "../includes/NodeOfTrees.h"
//#include "../classes/Tree.cpp"

using namespace std;

bool cmp(vector<Node<NodeOfTrees*>*>childNodes, NodeOfTrees* value)
{
	if (*childNodes[0]->value == *value)
		return 1;
	else
		return 0;
}

struct nodeCmp {
      bool operator()( const NodeOfTrees* n1, const NodeOfTrees* n2 ) const {
        return *n1 < *n2;
      }
};

int main(int argc, char** argv)
{
	NodeOfTrees* n1 = new NodeOfTrees(1, NULL);
	NodeOfTrees* n2 = new NodeOfTrees(1, NULL);
	NodeOfTrees* n3 = new NodeOfTrees(0, NULL);

	map<NodeOfTrees*, unsigned int, nodeCmp> myMap;






	/*========== SIMPLE COMPARE-TEST ==========*/
/*	NodeOfTrees* n1 = new NodeOfTrees(1, NULL);
	NodeOfTrees* n2 = new NodeOfTrees(1, NULL);
	NodeOfTrees* n3 = new NodeOfTrees(0, NULL);

	cout << "simple compare test: ";
	cout << (*n1==*n2);				// output: 1
	cout << (*n1==*n3);				// output: 0
	cout << endl;
*/

	/*========== FUNCTION COMPARE-TEST ==========*/
/*	vector<Node<NodeOfTrees*>* > childNodes;
	childNodes.push_back(new Node<NodeOfTrees*>(n1));

	cout << "function compare test: ";
	cout << cmp(childNodes, n1);			// output: 1
	cout << cmp(childNodes, n2);			// output: 1
	cout << cmp(childNodes, n3);			// output: 0
	cout << endl;*/
	return 0; //EXIT_SUCCESS;
}

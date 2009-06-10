/**
 * @file
 * @author  Gruppe 2
 * @version 1.0
 *
 * @section DESCRIPTION
 *
 * This program calculates a translation table, which is used during a translation to find the best hypothesis.
 * It expects 3 parameters: a <b>source-doc</b>, a <b>target-doc</b> and the <b>alignment</b>.
 * It outputs the translation-table in this format line by line:
 * 		<double> relFreq_f <double> relFreq_e # <string> fWord # <string> eWord
 */

#include <string>
#include <iostream>
#include <vector>
//#include "../classes/Tree.h"
#include "../classes/Tree.cpp"

using namespace std;

int main(int argc, char** argv)
{
	Tree<unsigned int> *t = new Tree<unsigned int>(0);

	vector<unsigned int> v;
	v.push_back(1);
	v.push_back(1);

	t->insert(v);
	t->insert(v);

	vector<unsigned int> w;
	w.push_back(1);
	w.push_back(0);
	t->insert(w);

	cout << t->getRoot()->childNodes[0]->childNodes[0]->count << endl;
	return 0; //EXIT_SUCCESS;
}

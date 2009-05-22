
#include <iostream>
#include <vector>
#include "../classes/Bleu.h"
#include "../classes/Lexicon.h"

using namespace std;

static Lexicon f;

int main()
{
	vector<unsigned int> trans = f.insertSentence("Dies ist ein Test");
	vector<unsigned int> ref = f.insertSentence("ein Test Dies ist");
	cout << trans[1] << trans[2] << trans[3] << endl;
	cout << f.getWord(trans[1]) << f.getWord(trans[2]) << f.getWord(trans[3]) << endl;
	//Bleu *current = new Bleu(trans,ref);

	return 0;
}

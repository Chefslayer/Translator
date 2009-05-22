#include <iostream>
#include <vector>
#include "../classes/Lexicon.h"
#include "../includes/functions.h"

using namespace std;

	static Lexicon f;
	static Lexicon e;

int main()
{
	unsigned int intWordF = f.insertWord("bambini");
	unsigned int intWordE = e.insertWord("child");
	vector<unsigned int> intSentF = f.insertSentence("la vida");
	vector<unsigned int> intSentE = e.insertSentence("life is life");

	for (int i = 0; i < intSentE.size(); i++)
		cout << intSentE[i] << endl;
	for (int i = 0; i < intSentF.size(); i++)
		cout << intSentF[i] << endl;
	cout << "Die Ausgabe soll sein: bambini, child, 1, 1 "<< endl;
	cout << "Die Ausgabe ist: " << f.getWord(intWordF) << ", " << e.getWord(intWordE) << ", " << f.getNum("bambini") << ", " << e.getNum("child") << endl;

	return 0;
}

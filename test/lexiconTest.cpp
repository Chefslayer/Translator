
#include "../classes/Lexicon.h"
#include <iostream>

using namespace std;

	static Lexicon f("italienisch");
	static Lexicon e("englisch");

int main()
{
	int intWordF = f.insert("bambini");
	int intWordE = e.insert("child");


	cout << "Die Ausgabe soll sein: bambini, child, 1, 1 "<< endl;
	cout << "Die Ausgabe ist: " << f.getWord(intWordF) << ", " << e.getWord(intWordE) << ", " << f.getNum("bambini") << ", " << e.getNum("child") << endl;

	return 0;
}

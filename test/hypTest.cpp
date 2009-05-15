
#include "../includes/hypothesis.h"
#include <iostream>

using namespace std;

int main()
{
	Hypothesis* h = new Hypothesis(NULL,0,0);
	Hypothesis* i = new Hypothesis(h,42,23);
	cout << "Die Ausgabe soll sein: NULL, 42, 23" << endl;
	cout << "Die Ausgabe ist: " << i->prevHyp->prevHyp  << ", " << i->totalCosts <<", " << i->trans << endl;
return 0;
}

/**
 * @file
 * @author  Gruppe 2
 * @version 1.0
 *
 * @section DESCRIPTION
 *
 * This program translates a source-document line by line.
 * It expects 2 parameters: a <b>translation-table</b> and the <b>source-document</b> which is going to be translated.
 * Output is the guessed translation line by line.
 */

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <utility>
#include <math.h>
#include <list>
#include <algorithm>
#include "includes/constants.h"
#include "classes/Lexicon.h"
#include "includes/recombHypothesis.h"
#include "includes/functions.h"
#include "includes/output.h"

using namespace std;

static Lexicon f;
static Lexicon e;

/**
 * holds information about a phrasepair from a translation-table.
 */
struct trans_phrase_tab_struct
{
	/// relative Frequence of F
	double relFreqF;
	/// relative Frequence of E
	double relFreqE;

	/// word-codes of the source-phrase
	vector<unsigned int> f;
	/// word-codes of the target-phrase
	vector<unsigned int> e;
};

/**
 * holds the A* table-row
 */
struct A_star_row
{
	/// pointer to the hypo for a phrase
	recombHypothesisEntry* hypo;

	/// translation of the sentence part from the end to here.
	string s_trans;

	/// score sum
	double f,
	/// score: phrase-costs
		g,
	///score: best path to hypo
		h;
	///costs for the sentence part from the end to here.
	double costs;

	bool operator<(A_star_row& n) const
	{
		return f < n.f;
	};
};

/**
 * searches a translation for a given line of texA_star_rowt.
 *
 * \param words a vector of words which will be translatet
 * \param translationtab table of translations
 * \return last recombHypothesis
 */
recombHypothesis* searchTranslation(vector<unsigned int> &words, vector<trans_phrase_tab_struct>  &translationtab)
{
	vector< recombHypothesis* > hypos;
	hypos.resize(words.size());
	vector<unsigned int> tmp;

	for (unsigned int hypoNr=0; hypoNr<hypos.size(); hypoNr++)
	{
		hypos[hypoNr] = new recombHypothesis;
	}

	for (unsigned int hypoNr=0; hypoNr<hypos.size(); hypoNr++)
	{
		recombHypothesis* prev = (hypoNr==0) ? NULL : hypos[hypoNr-1];

		// search for all phrases for the current hypo
		bool found_at_least_one_hypo = false;
		for (unsigned int phraseLength = 1; phraseLength <= MAX_PHRASE_LENGTH && hypoNr+phraseLength-1 < words.size(); phraseLength++)
		{
			vector<unsigned int> phraseF;
			phraseF.clear();
			for (unsigned int k = 0; k < phraseLength; k++)
			{
				phraseF.push_back(words[hypoNr+k]);
			}
			// search all possible translations and save them as hypos

			// search for first occurance of phraseF in transtab
			unsigned int transTabPos = 0;
			while (transTabPos < translationtab.size() && phraseF != translationtab[transTabPos].f)
			{
				transTabPos++;
			}

			// search for all following occurances of phraseF in transtab
			while (transTabPos < translationtab.size() && phraseF == translationtab[transTabPos].f)
			{
				found_at_least_one_hypo = true;

				recombHypothesisEntry *recombHypoEntry = new recombHypothesisEntry();
				recombHypoEntry->costs = 0.5*translationtab[transTabPos].relFreqF + 0.5*translationtab[transTabPos].relFreqE;

				recombHypoEntry->trans = translationtab[transTabPos].e;
				recombHypoEntry->prev = prev;

				vector<recombHypothesisEntry*>* entries = &(hypos[hypoNr+phraseLength-1]->entries);

				// check if this is the best hypo

				double new_costs = ((prev==NULL) ? 0 : prev->costs) + recombHypoEntry->costs;

				if (entries->size() == 0 || hypos[hypoNr+phraseLength-1]->costs > new_costs)
				{
					// safe costs and bestEntry
					hypos[hypoNr+phraseLength-1]->costs = new_costs;
					hypos[hypoNr+phraseLength-1]->bestEntry = entries->size();
				}
				entries->push_back(recombHypoEntry);

				transTabPos++;
			}
		}

		if (!found_at_least_one_hypo)
		{
			// insert '?'
			vector<unsigned int> tmp;
			tmp.push_back(0);
			
			recombHypothesisEntry *recombHypoEntry = new recombHypothesisEntry();
			recombHypoEntry->costs = 20;
			recombHypoEntry->trans = tmp;
			recombHypoEntry->prev = prev;

			vector<recombHypothesisEntry*>* entries = &(hypos[hypoNr]->entries);

			// check if this is the best hypo
			double new_costs = ((prev==NULL) ? 0 : prev->costs) + recombHypoEntry->costs;
			if (entries->size() == 0 || hypos[hypoNr]->costs > new_costs)
			{
				// safe costs and bestEntry
				hypos[hypoNr]->costs = new_costs;
				hypos[hypoNr]->bestEntry = entries->size();
			}
			entries->push_back(recombHypoEntry);
		}
	}
	
	// return last recombHypo
	return hypos[hypos.size()-1];
}

int main(int argc, char* argv[])
{
	if (argc < 3)
	{
		cerr << "ERROR: not enough parameters" << endl << "Usage: " << argv[0] << " translation-table source-document" << endl;
		return 0; // EXIT_FAILURE;
	}

	// open files
	ifstream trans_tab(argv[1]);
	ifstream src_doc(argv[2]);
	if (!trans_tab.good())
	{
		cerr << "ERROR: Opening translation table ("<< argv[1] <<") failed." << endl;
		return 1; // EXIT_FAILURE;
	}
	if (!src_doc.good())
	{
		cerr << "ERROR: Opening source document ("<< argv[2] <<") failed." << endl;
		return 1; // EXIT_FAILURE;
	}

	unsigned int i = 0;
	vector<struct trans_phrase_tab_struct> trans_phrase_tab_vec;
	trans_phrase_tab_vec.resize(VECTOR_INIT_SIZE);
	string line;

	// read trans_tab into trans_phrase_tab_vec
	while (getline(trans_tab, line))
	{
//		if (line.size()<12)
//			continue;

		struct trans_phrase_tab_struct current;
		double temp;
       		// line is formatted like: "<double> <double> # <string> ... <string> # <string> ... <string> "

		vector<string> line_vec = stringSplit(line, "#");
		// watch out for spaces!
		// line_vec[0] == "<double> <double> "
		// line_vec[1] == " <string> ... <string> "
		// line_vec[2] == " <string> ... <string> "

		vector<string> freqs_vec = stringSplit(line_vec[0], " ");

		istringstream isstrF(freqs_vec[0]);
		isstrF >> temp;
		current.relFreqF = temp;

		istringstream isstrE(freqs_vec[1]);
		isstrE >> temp;
		current.relFreqE = temp;

		vector<string> tempV;

		current.f = f.insertSentence(stringSplit(line_vec[1].substr(1,line_vec[1].size()-2), " "));
		current.e = e.insertSentence(stringSplit(line_vec[2].substr(1,line_vec[2].size()-2), " "));

		// insert src phrase
/*		tempV.clear();
		tempV = stringSplit(line_vec[1], " ");
		tempV.erase(tempV.begin());
		is.h:45: error: multiple types in onetempV.pop_back();
		current.f = f.insertSentence(tempV);
*/
		// insert target phrase
/*		tempV.clear();
		tempV = stringSpls_transit(line_vec[2], " ");
		tempV.erase(tempV.begin());
		tempV.pop_back();
		current.e = etrans.insertSentence(tempV);*/

		if (i >= trans_phrase_tab_vec.size())
		{
			trans_phrase_tab_vec.resize(trans_phrase_tab_vec.size() + VECTOR_RESIZE);
 		}
		trans_phrase_tab_vec[i] = current;
		// cout << f.getWord(current.f) << " " << current.relFreqF << endl;
		i++;
//		if (i/100==(double)i/(double)100)
//			cout<< "line" << i <<endl;
//		if (i>TRAINING_LINES) break;
	}
	trans_phrase_tab_vec.resize(i);

	// translate src_doc
  	/* output line is formated like:
	 * "<double>#<string> ... <string>"
	 * "<double>#<string> ... <string>"
	 * "<double>#<string> ... <string>"
	 * #
	 * "<double>#<string> ... <string>"
	 * ...
	 */
	while (getline(src_doc, line))
	{
		vector<string> stringwords = stringSplit(line, " ");
		vector<unsigned int> words(stringwords.size(), 0);

		for (unsigned int i = 0; i < stringwords.size(); i++)
		{
			words[i] = f.getNum(stringwords[i]);
		}

		recombHypothesis* lastHypo = searchTranslation(words, trans_phrase_tab_vec);

		// score for complete translation
		double score = (lastHypo==NULL)?100:lastHypo->costs;

		/************ output best translation ************/

		recombHypothesis* currentHypo = lastHypo;
		string translation = "";
		while (currentHypo != NULL)
		{
			string tmp="";

			vector<unsigned int>* trans = &(currentHypo->entries[currentHypo->bestEntry]->trans);
			for (unsigned int i = 0; i < trans->size(); ++i )
			{
				tmp += (tmp== ""?"":" ") + e.getWord((*trans)[i]);
			}
			translation = tmp+" "+translation;

			currentHypo = currentHypo->entries[currentHypo->bestEntry]->prev;
		}

		cout << score <<"#"<< translation << endl;

		/************ A* Search ************/
		unsigned int hypos_to_print = KEEP_N_BEST_HYPOS-1;

		currentHypo = lastHypo;

		vector<A_star_row> A_star_tab;
		string last_s_trans = "";
		double last_costs = 0;

		bool end = false;

		while (hypos_to_print && !end)
		{
			if (currentHypo != NULL)
			{
				// search for new expansions
				for (unsigned int entryNr=0; entryNr<currentHypo->entries.size(); entryNr++)
				{
					recombHypothesisEntry* currentEntry = currentHypo->entries[entryNr];
		
					// f = g+h
					A_star_row row;
					row.g = currentEntry->costs + last_costs;
					row.h = (currentEntry->prev==NULL) ? 0 : currentEntry->prev->costs;
					row.f = row.g + row.h;
					row.s_trans = "";

					// Übersetzung der aktuellen Phrase
					for (unsigned int i = 0; i<currentEntry->trans.size(); i++)
					{
						row.s_trans += (row.s_trans==""?"":" ") + e.getWord(currentEntry->trans[i]);
					}
					row.s_trans += (row.s_trans==""?"":" ") + last_s_trans;

					row.hypo = currentEntry;

					A_star_tab.push_back(row);
				}
			}

			// table empty? => no more translations possible
			if (A_star_tab.size()==0)
			{
				break;
			}

			// min f suchen
			vector<A_star_row>::iterator min_f_row = min_element(A_star_tab.begin(), A_star_tab.end());

			while (min_f_row->h == 0)
			{
				// ausgeben
				cout << min_f_row->g <<"#"<< min_f_row->s_trans << endl;

				// löschen
				A_star_tab.erase(min_f_row);
				hypos_to_print--;
				// table empty? => no more translations possible
				if (hypos_to_print==0 || A_star_tab.size()==0)
				{
					end = true;
					break;
				}
				min_f_row = min_element(A_star_tab.begin(), A_star_tab.end());
			}
			// table empty? => no more translations possible
			if (A_star_tab.size()==0 || end)
			{
				break;
			}

			// weiter expandieren
			currentHypo = min_f_row->hypo->prev;
			min_f_row->hypo->prev;
			
			// speicher aktuelle Übersetzung von Ende bis hier
			last_s_trans = min_f_row->s_trans;
			last_costs = min_f_row->g;

			// löschen der betrachteten min-f-row
			A_star_tab.erase(min_f_row);
		}

		cout << "#" << endl;
	}

	return 0; //EXIT_SUCCESS;
}

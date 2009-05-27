#include "Levenshtein.h"
#include <vector>
#include <string>
#include "Lexicon.h"

using namespace std;

Levenshtein::Levenshtein(vector<unsigned int> trans, vector<unsigned int> ref)
{
	// init vectors
	trans_v = trans;
	ref_v = ref;

	// init Matrix
	matrix.resize(trans.size()+1);

	for (unsigned int i=0; i<matrix.size(); i++)
		matrix[i].resize(ref.size()+1);

	for (unsigned int i=0; i<matrix[0].size(); i++)
		matrix[0][i]=i;

	for (unsigned int i=1; i<matrix.size(); i++)
		matrix[i][0] = i;

	
	// fill Matrix
	for (unsigned int i=1; i < matrix.size(); i++){
		for (unsigned int j=1; j<matrix[i].size(); j++){
			// matching
			unsigned int min = matrix[i-1][j-1];

			// deletion
			if (min > matrix[i-1][j])
					min = matrix[i-1][j];

			// insertion
			if (min > matrix[i][j-1])
					min = matrix[i][j-1];

			if (trans[i] != ref[j])
				matrix[i][j] = min + 1; 
			else
				matrix[i][j] = min;
		}
	}
}

unsigned int Levenshtein::getDistance()
{
	unsigned int i = matrix.size()-1;
	unsigned int j = matrix[matrix.size()-1].size()-1;
	return matrix[i][j];
}

string Levenshtein::getPath(Lexicon &lex)
{
	string path_ops = this->getPathOps();

	string path = "";
	unsigned int trans_counter = 0, ref_counter = 0;

	for (unsigned int i=0; i<path_ops.size(); i++)
	{
		switch (path_ops[i])
		{
			case 'm':
				path += "(m:"+lex.getWord(trans_v[trans_counter])+")";
				trans_counter++;
				ref_counter++;
				break;
			case 'i':
				path += "(i:"+lex.getWord(ref_v[ref_counter])+")";
				ref_counter++;
				break;
			case 'd':
				path += "(d:"+lex.getWord(trans_v[trans_counter])+")";
				trans_counter++;
				break;
		}
	}
	return path;
}

string Levenshtein::getPathOps()
{
	unsigned int i=matrix.size()-1;
	unsigned int j=matrix[0].size()-1;
	string res = "";
	while (!((i==0)&&(j==0)))
	{
		if(i==0){
			j--;
			res = "i" + res;
		}else{
			if (j==0){
				i--;
				res = "d" + res;
			}else{
				if ((matrix[i-1][j-1]<=matrix[i][j-1])&&(matrix[i-1][j-1]<=matrix[i-1][j])){
					i--;
					j--;
					res = "m" + res;
				}else{
					if (matrix[i][j-1]<matrix[i-1][j]){
						j--;
						res = "d" + res;
					}else{
						if (matrix[i][j-1]==matrix[i-1][j]){
							if (i<=j){
								j--;
								res = "i" + res;
							}else{
								i--;
								res = "d" + res;
							}
						}else{
							i--;
							res = "d" + res;
						}
					}
				}
			}
		}
	}
	return res;
}

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include "functions.h"

using namespace std;

/**
* splits a string into tokens
*
* \param str the string to split
* \param delim delim[0] is used as delimiter
* \return a vector with all tokens
*/
vector<string> stringSplit(string str, string delim)
{
	vector<string> result;
	istringstream iss(str);
	string token;
	while (getline(iss, token, delim[0]))
	{
		result.push_back(token);
	}
	return result;
}


/**
 * @file
 * @author  Gruppe 2
 * @version 1.0
 *
 * @section DESCRIPTION
 *
 * This file holds overall used functions.
 */

#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

#include <string>
#include <vector>

using namespace std;

/**
* splits a string into tokens
*
* \param str the string to split
* \param delim delim[0] is used as delimiter
* \return a vector with all tokens
*/
vector<string> stringSplit(string str, string delim);

#endif

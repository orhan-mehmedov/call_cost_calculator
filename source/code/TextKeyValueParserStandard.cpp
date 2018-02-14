/*
 * TextKeyValueParserStandard.cpp
 *
 * Created on: Jun 16, 2016
 * Orhan Mehmedov
 * http://mehmed.info
 * License: GPL v3
 * https://www.gnu.org/licenses/gpl.html
 *
 */

#include "TextKeyValueParserStandard.hpp"

using namespace std;
using namespace CallCostCalculator;

TKeyValue
TextKeyValueParserStandard::operator()(const std::string& str, char delimiter) const
{
	TKey key;
	TValue value;

	size_t pos = str.find(delimiter);

	if(pos != string::npos)
	{
		key = str.substr(0, pos);
		value = str.substr(pos+1, string::npos);
	}
	else
	{
		key = str;//is not key=val, just flag...
	}

	return TKeyValue(key, value);
}

TextKeyValueParserStandard::~TextKeyValueParserStandard()
{

}


/*
 * StandardInput.cpp
 *
 * Created on: Jun 16, 2016
 * Orhan Mehmedov
 * http://mehmed.info
 * License: GPL v3
 * https://www.gnu.org/licenses/gpl.html
 *
 */

#include <stdexcept>

#include "StandardInput.hpp"
#include "TextKeyValueParserStandard.hpp"
#include "common.hpp"

using namespace std;
using namespace CallCostCalculator;

namespace CallCostCalculator
{
extern int g_Argc;
extern char **g_Argv;
}

StandardInput::StandardInput(std::auto_ptr<TextKeyValueParserInterface> parser)
try
:
m_parser(parser)
{
	parseInput();
}
catch(...)
{
	//TODO .....................
}

void StandardInput::parseInput()
{
	int i = 0;

	while(0 != *(g_Argv+i))
	{
		if (i >= g_Argc)
		{
			break;
		}

		string str(*(g_Argv+i));

		TKeyValue keyValue = (*m_parser)(str, stdInputParamValueDelimiter);

		m_KeyValues.insert(keyValue);

		++i;
	}
}

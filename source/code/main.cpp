/*
 * main.cpp
 *
 * Created on: Jun 15, 2016
 * Orhan Mehmedov
 * http://mehmed.info
 * License: GPL v3
 * https://www.gnu.org/licenses/gpl.html
 *
 */

#include <iostream>
#include <stdlib.h>

#include "ModeSelector.hpp"
#include "CallFeeCalculator.hpp"

using namespace std;
using namespace CallCostCalculator;

namespace CallCostCalculator
{
int g_Argc;
char ** g_Argv;
}

int main(int argc, char **argv)
{
	//Standard input parameters:
	g_Argc = argc;
	g_Argv = argv;

	try
	{
		ModeSelector& modeSelector = ModeSelector::getInstance();
		CallFeeCalculator& calculator = modeSelector.getMode();

		calculator.Calculate();
	}
	catch(const exception& e)
	{
		cerr << "Error occurred! Program will be terminated! "
				"Please, check next message and make sure "
				"input data is correct:\n";
		cerr << e.what() << endl;
		exit(-1);
	}
}

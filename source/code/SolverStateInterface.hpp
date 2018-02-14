/*
 * SolverStateInterface.hpp
 *
 * Created on: Jun 18, 2016
 * Orhan Mehmedov
 * http://mehmed.info
 * License: GPL v3
 * https://www.gnu.org/licenses/gpl.html
 *
 */

#ifndef CALLCOSTCALCULATOR_CODE_SOLVERSTATEINTERFACE_HPP_
#define CALLCOSTCALCULATOR_CODE_SOLVERSTATEINTERFACE_HPP_

#include "common.hpp"

namespace CallCostCalculator
{

class SolverStateInterface
{
public:
	virtual void handle(TEvent event) = 0;
	virtual ~SolverStateInterface(){}
};

}

#endif /* CALLCOSTCALCULATOR_CODE_SOLVERSTATEINTERFACE_HPP_ */

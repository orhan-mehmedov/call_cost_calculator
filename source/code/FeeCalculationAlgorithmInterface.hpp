/*
 * FeeCalculationAlgorithmInterface.hpp
 *
 * Created on: Jun 17, 2016
 * Orhan Mehmedov
 * http://mehmed.info
 * License: GPL v3
 * https://www.gnu.org/licenses/gpl.html
 *
 */

#ifndef CALLCOSTCALCULATOR_CODE_FEECALCULATIONALGORITHMINTERFACE_HPP_
#define CALLCOSTCALCULATOR_CODE_FEECALCULATIONALGORITHMINTERFACE_HPP_

#include "CallContextData.hpp"
#include "CallData.hpp"

namespace CallCostCalculator
{

class FeeCalculationAlgorithmInterface
{
public:
  virtual double calculateCallCost(TContext context, TCallData callData) = 0;
  virtual ~FeeCalculationAlgorithmInterface(){}
};

}

#endif /* CALLCOSTCALCULATOR_CODE_FEECALCULATIONALGORITHMINTERFACE_HPP_ */

/*
 * CallFeeCalculator.hpp
 *
 * Created on: Jun 16, 2016
 * Orhan Mehmedov
 * http://mehmed.info
 * License: GPL v3
 * https://www.gnu.org/licenses/gpl.html
 *
 */

#ifndef CALLCOSTCALCULATOR_CODE_CALLFEECALCULATOR_HPP_
#define CALLCOSTCALCULATOR_CODE_CALLFEECALCULATOR_HPP_

#include <memory>

#include "CallContextData.hpp"
#include "CallData.hpp"

namespace CallCostCalculator
{

typedef double TCallCost;

//Template Method
class CallFeeCalculator
{
  virtual void inputLogicalControl(TContext& context, TCallData& callData);

protected:
  virtual TContext getContextData() = 0;
  virtual TCallData getCallInfo() = 0;
  virtual TCallCost callCalculation(TContext context, TCallData callData) = 0;
  virtual void provideResult(TCallCost result) = 0;

public:
  void Calculate();
  virtual ~CallFeeCalculator();
};

} // namespace CallCalculator

#endif /* CALLCOSTCALCULATOR_CODE_CALLFEECALCULATOR_HPP_ */

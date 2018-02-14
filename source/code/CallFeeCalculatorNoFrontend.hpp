/*
 * CallFeeCalculatorNoFrontend.hpp
 *
 * Created on: Jun 16, 2016
 * Orhan Mehmedov
 * http://mehmed.info
 * License: GPL v3
 * https://www.gnu.org/licenses/gpl.html
 *
 */

#ifndef CALLCOSTCALCULATOR_CODE_CALLFEECALCULATORNOFRONTEND_HPP_
#define CALLCOSTCALCULATOR_CODE_CALLFEECALCULATORNOFRONTEND_HPP_

#include <memory>

#include "CallFeeCalculator.hpp"
#include "InputInterface.hpp"
#include "FeeCalculationAlgorithmInterface.hpp"

namespace CallCostCalculator
{

//particular implementation of the template
//no front-end - command line parameters + context file
//application is single shot - calculates concrete call fee and exits
//could be used with scripts etc. to calculate many calls...
//also easy to test with scripts...

class CallFeeCalculatorNoFrontend : public CallFeeCalculator
{
  std::auto_ptr<InputInterface> m_stdInputCallInfo;
  std::auto_ptr<InputInterface> m_fileAccountInfoInput;
  std::auto_ptr<TextKeyValueParserInterface> m_parser;
  std::auto_ptr<FeeCalculationAlgorithmInterface> m_algorithm;

protected:
  virtual TContext getContextData();
  virtual TCallData getCallInfo();
  virtual TCallCost callCalculation(TContext context, TCallData callData);
  virtual void provideResult(TCallCost result);

public:
  CallFeeCalculatorNoFrontend(
      std::auto_ptr<InputInterface> stdInputCallInfo,
      std::auto_ptr<InputInterface> fileAccountInfoInput,
      std::auto_ptr<TextKeyValueParserInterface> parser,
      std::auto_ptr<FeeCalculationAlgorithmInterface> algorithm
      );

  virtual ~CallFeeCalculatorNoFrontend();
};

} // namespace CallCalculator

#endif /* CALLCOSTCALCULATOR_CODE_CALLFEECALCULATORNOFRONTEND_HPP_ */

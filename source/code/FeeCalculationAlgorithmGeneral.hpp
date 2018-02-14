/*
 * FeeCalculationAlgorithmGeneral.hpp
 *
 * Created on: Jun 17, 2016
 * Orhan Mehmedov
 * http://mehmed.info
 * License: GPL v3
 * https://www.gnu.org/licenses/gpl.html
 *
 */

#ifndef CALLCOSTCALCULATOR_CODE_FEECALCULATIONALGORITHMGENERAL_HPP_
#define CALLCOSTCALCULATOR_CODE_FEECALCULATIONALGORITHMGENERAL_HPP_

#include <queue>
#include <vector>

#include "common.hpp"
#include "FeeCalculationAlgorithmInterface.hpp"

namespace CallCostCalculator
{

class FeeCalculationAlgorithmGeneral : public FeeCalculationAlgorithmInterface
{
protected:
	int secondsToBeChargedSolver(
			TEventsQueueAuto events,
			TFreeMinutesOnWeekends freeWeekendMinutes,
			bool hasFreeMinutesAtTheCallStartP,
			TFreeMinutesInsideOperatorLeft freeMinutesInsideOperatorLeftP);
public:
	virtual double calculateCallCost(TContext context, TCallData callData);
};

}


#endif /* CALLCOSTCALCULATOR_CODE_FEECALCULATIONALGORITHMGENERAL_HPP_ */

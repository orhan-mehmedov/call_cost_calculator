/*
 * ModeSelector.hpp
 *
 * Created on: Jun 16, 2016
 * Orhan Mehmedov
 * http://mehmed.info
 * License: GPL v3
 * https://www.gnu.org/licenses/gpl.html
 *
 */

#ifndef CALLCOSTCALCULATOR_CODE_MODESELECTOR_HPP_
#define CALLCOSTCALCULATOR_CODE_MODESELECTOR_HPP_

#include "CallFeeCalculator.hpp"

namespace CallCostCalculator
{

class ModeSelector
{
  CallFeeCalculator *mode;

  ModeSelector();
  ModeSelector(const ModeSelector&);
  void operator =(const ModeSelector&);
public:
  static ModeSelector& getInstance();

  CallFeeCalculator& getMode();

};

} // namespace CallCalculator

#endif /* CALLCOSTCALCULATOR_CODE_MODESELECTOR_HPP_ */

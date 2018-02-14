/*
 * StandardInput.hpp
 *
 * Created on: Jun 16, 2016
 * Orhan Mehmedov
 * http://mehmed.info
 * License: GPL v3
 * https://www.gnu.org/licenses/gpl.html
 *
 */

#ifndef CALLCOSTCALCULATOR_CODE_STANDARDINPUT_HPP_
#define CALLCOSTCALCULATOR_CODE_STANDARDINPUT_HPP_

#include <map>
#include <string>
#include <memory>

#include "BaseInput.hpp"
#include "TextKeyValueParserInterface.hpp"

namespace CallCostCalculator
{

class StandardInput : public BaseInput
{
  std::auto_ptr<TextKeyValueParserInterface> m_parser;
protected:
  virtual void parseInput();

public:
  StandardInput(std::auto_ptr<TextKeyValueParserInterface> parser);
};

} // namespace CallCalculator

#endif /* CALLCOSTCALCULATOR_CODE_STANDARDINPUT_HPP_ */

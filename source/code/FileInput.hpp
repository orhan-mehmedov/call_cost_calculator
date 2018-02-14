/*
 * FileInput.hpp
 *
 * Created on: Jun 16, 2016
 * Orhan Mehmedov
 * http://mehmed.info
 * License: GPL v3
 * https://www.gnu.org/licenses/gpl.html
 *
 */

#ifndef CALLCOSTCALCULATOR_CODE_FILEINPUT_HPP_
#define CALLCOSTCALCULATOR_CODE_FILEINPUT_HPP_

#include <map>
#include <memory>

#include "BaseInput.hpp"

namespace CallCostCalculator
{

typedef std::map<TKey, TValue> TFileInput;

class FileInput : public BaseInput
{
  std::auto_ptr<std::string> m_file;
  std::auto_ptr<TextKeyValueParserInterface> m_parser;

protected:
  virtual void parseInput();

public:
  FileInput(
      std::auto_ptr<std::string> file,
      std::auto_ptr<TextKeyValueParserInterface> parser);
  virtual ~FileInput();
};

}

#endif /* CALLCOSTCALCULATOR_CODE_FILEINPUT_HPP_ */

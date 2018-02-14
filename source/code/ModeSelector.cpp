/*
 * ModeSelector.cpp
 *
 * Created on: Jun 16, 2016
 * Orhan Mehmedov
 * http://mehmed.info
 * License: GPL v3
 * https://www.gnu.org/licenses/gpl.html
 *
 */

#include <string>
#include <stdexcept>

#include "ModeSelector.hpp"
#include "CallFeeCalculatorNoFrontend.hpp"
#include "StandardInput.hpp"
#include "FileInput.hpp"
#include "TextKeyValueParserStandard.hpp"
#include "FeeCalculationAlgorithmGeneral.hpp"

using namespace std;
using namespace CallCostCalculator;

ModeSelector::ModeSelector() : mode()
{

}

ModeSelector& ModeSelector::getInstance()
{
  static ModeSelector modeSelector;

  return modeSelector;
}

CallFeeCalculator& ModeSelector::getMode()
{
  //configure the kind of application:
  //place to make different choices:
  //this is kind of "simple" factory

  if(0 == mode)
  {
    auto_ptr<TextKeyValueParserInterface>
      parserStdIn(new TextKeyValueParserStandard);

    auto_ptr<TextKeyValueParserInterface>
      parserFileIn(new TextKeyValueParserStandard);

    auto_ptr<TextKeyValueParserInterface>
      parserCallCalculator(new TextKeyValueParserStandard);

    auto_ptr<InputInterface> stdIn(new StandardInput(parserStdIn));
    auto_ptr<InputInterface> fileIn;

    auto_ptr<FeeCalculationAlgorithmInterface> calculationAlgorithm(
        new FeeCalculationAlgorithmGeneral());

    if(stdIn->isKeyExist(cstrSubscriberAccount))
    {
      auto_ptr<string> subscriberAccountFile(
          new string(stdIn->getParamValue(cstrSubscriberAccount)));

      fileIn.reset(new FileInput(subscriberAccountFile, parserFileIn));
    }

    if(stdIn->isKeyExist(cstrFrontend))
    {
      if(cstrFrontEndNO == stdIn->getParamValue(cstrFrontend))
      {
        //call info by stdin
        //subscriber account / call context -> from file!
        mode = new CallFeeCalculatorNoFrontend(
            stdIn, fileIn, parserCallCalculator,
            calculationAlgorithm);
      }
      //else front end = YES
    }
    //others...
  }

  if(0 == mode)
  {
    throw invalid_argument(
        "Can not select mode from input parameters!");
  }

  return *mode;
}

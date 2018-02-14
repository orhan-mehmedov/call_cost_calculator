/*
 * FileInput.cpp
 *
 * Created on: Jun 16, 2016
 * Orhan Mehmedov
 * http://mehmed.info
 * License: GPL v3
 * https://www.gnu.org/licenses/gpl.html
 *
 */

#include <fstream>
#include <stdexcept>

#include "FileInput.hpp"

#include "common.hpp"

using namespace std;
using namespace CallCostCalculator;

namespace CallCostCalculator
{
}

FileInput::FileInput(
    auto_ptr<string> file,
    auto_ptr<TextKeyValueParserInterface> parser)
:
  m_file(file), m_parser(parser)
{
  parseInput();
}

void FileInput::parseInput()
{
  ifstream inputFile;

  try
  {
    inputFile.open(m_file->c_str(), ios::in);

    if(!inputFile.is_open())
    {
      throw runtime_error(string("FATAL! Can not open file: ") + *m_file);
    }

    while(!inputFile.eof())
    {
      string line;

      getline(inputFile, line);

      //TODO: check flags

      if(string::npos != line.find(fileInputCommentStart))
      {
        continue;
      }

      TKeyValue keyValue = (*m_parser)(line, fileInputParamValueDelimiter);

      if(0 < keyValue.first.length())
      {
        m_KeyValues.insert(keyValue);
      }
    }
  }
  catch(...)
  {
    inputFile.close();
    throw;
  }

  inputFile.close();
}

FileInput::~FileInput()
{

}






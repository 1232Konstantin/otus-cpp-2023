#include "CmdCommandReceiver.h"

#include <memory>
#include <string>
#include <iostream>

using namespace Bulk;

std::shared_ptr<ICommandReceiver> CommandReceiverFactory::Create(const OnCommandReceived& inCommandReceivedCallback)
{
  return std::make_shared<FCmdCommandReceiver>(inCommandReceivedCallback);
}

FCmdCommandReceiver::FCmdCommandReceiver(const OnCommandReceived& inCommandReceivedCallback)
  : ICommandReceiver(inCommandReceivedCallback)
{}

//-------------------------------------------------
// TODO replace with boost
// https://stackoverflow.com/questions/216823/how-to-trim-an-stdstring
// trim from start (in place)
static inline void ltrim(std::string& s) {
  s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
    return !std::isspace(ch);
    }));
}

// trim from end (in place)
static inline void rtrim(std::string& s) {
  s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
    return !std::isspace(ch);
    }).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string& s) {
  rtrim(s);
  ltrim(s);
}
//------------------------------------------------

bool FCmdCommandReceiver::Begin()
{
  std::string line;
  while (std::getline(std::cin, line))
  {
    trim(line);
    CommandReceivedCallback(line, false);
  }

  CommandReceivedCallback("", true);
  return true;
}
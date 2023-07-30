#include "CmdApplication.h"

#include <iostream>
#include <sstream>
#include <vector>

using namespace Editor;

const std::string EXIT_KEYWORD("Exit");
const std::string CREATE_DOCUMENT_KEYWORD("CreateDocument");
const std::string IMPORT_DOCUMENT_KEYWORD("ImportDocument");
const std::string EXPORT_DOCUMENT_KEYWORD("ExportDocument");
const std::string CREATE_PRIMITIVE_KEYWORD("CreatePrimitive");
const std::string DELETE_PRIMITIVE_KEYWORD("DeleteLastNPrimitives");

FCmdApplication::FCmdApplication(std::istream& in)
  : Stream(in)
  , IsRunning(true)
{
  Gui = GUIFactory::Create();
  Storage = StorageFactory::Create(Gui);
  InputController = InputControllerFactory::Create(Gui, Storage);
}

bool FCmdApplication::Begin()
{
  std::cout << "Application start" << std::endl;
  return EventLoop();
}

bool FCmdApplication::EventLoop()
{
  std::cout << "Main loop start" << std::endl;

  while (IsRunning)
  {
    Gui->DrawAll();

    if (!HandleInput())
    {
      std::cout << "Input handling failed, terminating" << std::endl;
      return false;
    }
  }

  std::cout << "Main loop end, terminating" << std::endl;
  return true;
}

bool FCmdApplication::HandleInput()
{
  std::string line;
  std::getline(Stream, line);
  std::stringstream ssline(line);

  std::vector<std::string> words;
  std::string word;
  while (std::getline(ssline, word, ' '))
  {
    if (word.empty())
    {
      continue;
    }

    words.push_back(word);
  }

  if (words.empty())
  {
    return false;
  }

  if (words[0] == EXIT_KEYWORD)
  {
    IsRunning = false;
    return true;
  }

  if (words[0] == CREATE_DOCUMENT_KEYWORD)
  {
    return InputController->CreateDocument(words[1]);
  }

  if (words[0] == IMPORT_DOCUMENT_KEYWORD)
  {
    return InputController->ImportDocument(words[1]);
  }

  if (words[0] == EXPORT_DOCUMENT_KEYWORD)
  {
    return InputController->ExportDocument(words[1]);
  }

  if (words[0] == CREATE_PRIMITIVE_KEYWORD)
  {
    std::vector<std::pair<int, int>> coordinates{};
    for (size_t i = 1; i < words.size(); ++i)
    {
      int x = 0;
      int y = 0;

      size_t comma_pos = words[i].find(',');
      if (comma_pos == std::string::npos)
      {
        return false;
      }

      x = std::atoi(words[i].substr(1, comma_pos - 1).c_str());
      y = std::atoi(words[i].substr(comma_pos + 1, words[i].size() - 1 - comma_pos - 1).c_str());

      coordinates.push_back({ x, y });
    }

    return InputController->CreatePrimitive(coordinates);
  }

  if (words[0] == DELETE_PRIMITIVE_KEYWORD)
  {
    return InputController->DeleteLastNPrimitives(std::atoi(words[1].c_str()));
  }

  return true;
}

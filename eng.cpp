#include <string>
#include <unordered_set>
#include <fstream>
#include <algorithm>
#include <cctype>
#include <vector>
#include <iostream>

int main()
{
  int success = 0;
  int fail = 0;
  int before = 0;
  int after = 0;

  std::ifstream infile("in.txt");
  std::ifstream checkfile("check.txt");

  std::unordered_set<std::string> inwords;
  std::vector<std::string> checkwords;
  std::vector<std::string> mistakes;

  std::ofstream outfile("out.txt");
  std::ofstream misfile("mistakes.txt");

  std::string line;
  while (std::getline(infile, line))
  {
    auto data = line.substr(0, line.find('.'));
    std::transform(data.begin(), data.end(), data.begin(),
      [](unsigned char c) { return std::toupper(c); });
    inwords.insert(data);
  }

  while (std::getline(checkfile, line))
  {
    line.erase(std::find_if(line.rbegin(), line.rend(), [](unsigned char ch) {
      return !std::isspace(ch);
      }).base(), line.end());
    checkwords.push_back(line);
  }

  before = inwords.size();

  for (const auto& word : checkwords)
  {
    if (inwords.count(word))
    {
      inwords.erase(word);
      ++success;
      continue;
    }

    mistakes.push_back(word);
    ++fail;
  }

  after = inwords.size();

  std::cout << "before = " << before
    << "\nafter = " << after
    << "\ncheck = " << checkwords.size()
    << "\nsuccess = " << success
    << "\nmistakes = " << fail << std::endl;

  for (const auto& word : inwords)
  {
    outfile << word << ".\n";
  }
  outfile.close();

  for (const auto& word : mistakes)
  {
    misfile << word << ".\n";
  }
  misfile.close();

  return 0;
}
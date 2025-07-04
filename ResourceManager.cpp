#include "ResourceManager.h"
#include <iostream>
#include <string>

void ResourceManager::loadResources(std::string &source, std::unordered_map<std::string, std::string> &resourceMap)
{
  std::ifstream readFile(source + ".txt");
  std::string line;

  bool pairSection; // false: key, true: value
  std::string key;
  std::string value;

  while (std::getline(readFile, line))
  {
    pairSection = false;
    key = "";
    value = "";

    for (char c : line)
    {
      if (!pairSection) // Add to key
      {
        if (c == ':') // If char is splitter ':'
        {
          pairSection = true;
          continue;
        }
        key += c;
      }
      else // Add to value
      {
        value += c;
      }
    }

    resourceMap.at(key) = value; // Add resource and value to resourceMap
  }

  readFile.close();
}

void ResourceManager::loadResources(std::string source)
{
  if (source == "saveData")
    loadResources(source, saveData);
  else if (source == "settings")
    loadResources(source, settings);
}

void ResourceManager::saveResources(std::string &destination, std::unordered_map<std::string, std::string> &resourceMap)
{
  std::ofstream writeFile(destination + ".txt");

  for (std::pair<std::string, std::string> resource : resourceMap)
    writeFile << resource.first << ":" << resource.second << "\n";

  writeFile.close();
}

void ResourceManager::saveResources(std::string destination)
{
  if (destination == "saveData")
    saveResources(destination, saveData);
  else if (destination == "settings")
    saveResources(destination, settings);
}

std::string ResourceManager::getStringResource(std::string source, std::string resource)
{
  if (source == "settings") // todo: flip these
    return (settings.at(resource));
  else if (source == "saveData")
    return (saveData.at(resource));
  else           // In case of invalid source
    return (""); // Return nothing
}

double ResourceManager::getNumberResource(std::string source, std::string resource)
{
  std::string rawValue;
  double value;

  if (source == "settings") // todo: flip these
    rawValue = settings.at(resource);
  else if (source == "saveData")
    rawValue = saveData.at(resource);
  else // In case of invalid source
    return 0;

  try // Check to see if value is a valid number
  {
    value = std::stod(rawValue);
  }
  catch (int e)
  { // In case of invalid value
    return 0;
  }

  return std::stof(rawValue);
}

void ResourceManager::setResource(std::string source, std::string resource, std::string value)
{
  if (source == "saveData")
    saveData.at(resource) = value;
  else if (source == "settings")
    settings.at(resource) = value;
}

void ResourceManager::setResource(std::string source, std::string resource, double value)
{
  setResource(source, resource, std::to_string(value));
}
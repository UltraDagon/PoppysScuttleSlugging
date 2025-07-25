#include "ResourceManager.h"

bool ResourceManager::purchaseUpgrade(std::string name)
{
  int currentLevel = getNumberResource("saveData", name);
  int currentGold = getNumberResource("saveData", "gold");
  std::string upgradeName = name + std::to_string(currentLevel + 1);
  int price = INT_MAX;

  // If upgrade is not found (max level or incorrect name)
  if (upgradeCosts.count(upgradeName) == 0)
    return false;

  price = upgradeCosts.at(upgradeName);

  // If the player does not have enough gold to purchase the upgrade
  if (currentGold < price)
    return false;

  std::cout << "\"Bought\" upgrade! Gold: " << currentGold << " -> " << currentGold - price << std::endl;

  return true;
}

void ResourceManager::loadAllResources()
{
  loadResources("saveData", saveData);
  loadResources("settings", settings);
}

void ResourceManager::loadResources(std::string source, std::unordered_map<std::string, std::string> &resourceMap)
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

    resourceMap.emplace(key, value); // Add resource and value to resourceMap
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

void ResourceManager::saveAllResources()
{
  saveResources("saveData", saveData);
  saveResources("settings", settings);
}

void ResourceManager::saveResources(std::string destination, std::unordered_map<std::string, std::string> &resourceMap)
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
  if (source == "saveData")
  {
    // If the resource isn't in saveData, add it with value ""
    if (saveData.count(resource) == 0)
      saveData.emplace(resource, "");
    return (saveData.at(resource));
  }
  else if (source == "settings")
  {
    // If the resource isn't in settings, add it with value ""
    if (settings.count(resource) == 0)
      settings.emplace(resource, "");
    return (settings.at(resource));
  }
  else           // In case of invalid source
    return (""); // Return nothing
}

double ResourceManager::getNumberResource(std::string source, std::string resource)
{
  std::string rawValue = getStringResource(source, resource);
  double value;

  if (rawValue == "")
    return 0;

  try // Check to see if value is a valid number
  {
    value = std::stod(rawValue);
  }
  catch (int e)
  { // In case of invalid value
    value = 0;
  }

  return value;
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
#include <fstream>
#include <unordered_map>
#include <typeinfo>

#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

// Note that resources cannot have ':' anywhere within them, as ':' is used to separate keys and values when saving/loading.

class ResourceManager
{
private:
  std::unordered_map<std::string, std::string> settings;
  std::unordered_map<std::string, std::string> saveData = {
      {"gold", "0"}};

  void loadResources(std::string source, std::unordered_map<std::string, std::string> &resourceMap);

  void saveResources(std::string destination, std::unordered_map<std::string, std::string> &resourceMap);

public:
  // ResourceManager();

  // TODO: make default save/load that does both settings and savedata
  void loadAllResources();

  void saveAllResources();

  void loadResources(std::string source);

  void saveResources(std::string destination);

  /**
   * @param resource Name of resource to get from source
   * @param source Source to get resource from. Valid sources: "settings", "saveData"
   * @return The value of the resource requested as a string
   */
  std::string getStringResource(std::string source, std::string resource);

  /**
   * @param resource Name of resource to get from source
   * @param source Source to get resource from. Valid sources: "settings", "saveData"
   * @return The value of the resource requested as a double. If the source/value are invalid or the resource is not found, returns 0
   */
  double getNumberResource(std::string source, std::string resource);

  void setResource(std::string source, std::string resource, std::string value);

  void setResource(std::string source, std::string resource, double value);
};

#endif
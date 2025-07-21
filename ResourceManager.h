#include <fstream>
#include <unordered_map>
#include <typeinfo> // Todo: see if I can remove this

#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

/**
 * Resource manager for saveData.txt and settings.txt.
 * 
 * Note that resources cannot have ':' anywhere within them, as ':' is used to separate keys and values when saving/loading.
 */
class ResourceManager
{
private:
  std::unordered_map<std::string, std::string> settings;
  std::unordered_map<std::string, std::string> saveData = {
      {"gold", "0"}};

  /**
   * Load resources from a text file.
   * 
   * @param source The name of the text file to load resources from ("saveData" or "settings")
   * @param resourceMap The resource map to load the text file's resources into
   */
  void loadResources(std::string source, std::unordered_map<std::string, std::string> &resourceMap);

  /**
   * Save resources to a text file.
   * 
   * @param destination The name of the text file to save resources to ("saveData" or "settings")
   * @param resourceMap The resource map containing the resources that will be saved to the text file
   */
  void saveResources(std::string destination, std::unordered_map<std::string, std::string> &resourceMap);

public:
  // ResourceManager();

  /**
   * Load the data from saveData.txt and settings.txt to the respective resource maps.
   */
  void loadAllResources();

  /**
   * Save the data to saveData.txt and settings.txt from the respective resource maps.
   */
  void saveAllResources();

  /**
   * Load the resources from a text file. 
   * 
   * @param source the text file to load resources from ("saveData" or "settings")
   */
  void loadResources(std::string source);

  /**
   * Save resources to a text file.
   * 
   * @param destination the text file to save resources to ("saveData" or "settings")
   */
  void saveResources(std::string destination);

  /**
   * Get a resource in the form of a string.
   * 
   * @param source source to get resource from ("saveData" or "settings")
   * @param resource same of resource to get from source
   * @return the value of the resource requested as a string
   */
  std::string getStringResource(std::string source, std::string resource);

  /**
   * Get a resource in the form of a number.
   *
   * @param source source to get resource from ("saveData" or "settings")
   * @param resource name of resource to get from source
   * @return the value of the resource requested as a double. If the source/value are invalid or the resource is not found, returns 0
   */
  double getNumberResource(std::string source, std::string resource);

  /**
   * Set the value of a resource.
   * 
   * @param source source of the resource ("saveData" or "settings")
   * @param resource name of the resource to be modified
   * @param value value to set the resource to in the form of a string
   */
  void setResource(std::string source, std::string resource, std::string value);

  /**
   * Set the value of a resource.
   * 
   * @param source source of the resource ("saveData" or "settings")
   * @param resource name of the resource to be modified
   * @param value value to set the resource to in the form of a double
   */
  void setResource(std::string source, std::string resource, double value);
};

#endif
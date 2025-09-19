#include <fstream>
#include <unordered_map>
#include <iostream>
#include <string>

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
  /// The scene will be changed to this char upon request by a scene
  char newScene = ' ';
  /// Costs of upgrading to each level of an upgrade
  const std::unordered_map<std::string, int> upgradeCosts = {
      {"r_level1", 10},
      {"r_level2", 20},
      {"r_level3", 30},
      {"r_level4", 40},
      {"r_level5", 50},
      {"-r_level6", 60},
      {"-r_level7", 70},
      {"-r_level8", 80},
      {"-r_level9", 90},
      {"-r_level10", 100},
      {"krug_level1", 10},
      {"krug_level2", 20},
      {"krug_level3", 30},
      {"krug_level4", 40},
      {"krug_level5", 50},
      {"-krug_level6", 60},
      {"-krug_level7", 70},
      {"-krug_level8", 80},
      {"-krug_level9", 90},
      {"-krug_level10", 100},
      {"q_level1", 10},
      {"q_level2", 20},
      {"q_level3", 30},
      {"q_level4", 40},
      {"q_level5", 50},
      {"-q_level6", 60},
      {"-q_level7", 70},
      {"-q_level8", 80},
      {"-q_level9", 90},
      {"-q_level10", 100},
      {"gold_gain_level1", 10},
      {"gold_gain_level2", 20},
      {"gold_gain_level3", 30},
      {"gold_gain_level4", 40},
      {"gold_gain_level5", 50},
      {"gold_gain_level6", 60},
      {"gold_gain_level7", 70},
      {"gold_gain_level8", 80},
      {"gold_gain_level9", 90},
      {"gold_gain_level10", 100},
      {"scuttle_defense_level1", 10},
      {"scuttle_defense_level2", 20},
      {"scuttle_defense_level3", 30},
      {"scuttle_defense_level4", 40},
      {"scuttle_defense_level5", 50},
      {"scuttle_defense_level6", 60},
      {"scuttle_defense_level7", 70},
      {"scuttle_defense_level8", 80},
      {"scuttle_defense_level9", 90},
      {"scuttle_defense_level10", 100}};

  /// Map of all settings and their values
  std::unordered_map<std::string, std::string> settings;
  /// Map of all saveData resources and their values
  std::unordered_map<std::string, std::string> saveData;

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
   * Get the cost of an upgrade.
   *
   * If the upgrade is max level or not found, returns -1.
   *
   * @param upgrade the upgrade to get the cost of. Ex: r_level3
   * @return the cost of the upgrade in gold
   */
  int getUpgradeCost(std::string upgrade);

  /**
   * Attempt to purchase an upgrade from the shop.
   *
   * @param resource the name of the upgrade/resource
   * @return whether or not the upgrade purchase succeeded
   */
  bool purchaseUpgrade(std::string resource);

  /**
   * Get the scene the Resource Manager requests to change to.
   *
   * @return the new scene to be changed to
   */
  char getNewScene();

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

  // TODO: Move these 2 vv to the top, I like voids at the bottom

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

  /**
   * Change the current scene.
   *
   * @param newScene the name of the scene to be switched to
   */
  void changeScene(char newScene_);
};

#endif
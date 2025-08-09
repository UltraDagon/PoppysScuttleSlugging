#ifndef KRUG_H
#define KRUG_H

#include <random>
#include "Entity.h"

class Krug : public Entity
{
private:
  struct LevelStats
  {
    int minGoldDrop;
    int maxGoldDrop;
    float bounceRefund;
    float qCharge;
    /// The minimum delay possible before spawning the next Krug (in seconds).
    float spawnDelayMin;
    /// The maximum delay possible before spawning the next Krug (in seconds).
    float spawnDelayMax;
  };

  const std::unordered_map<int, LevelStats> krugLevels = {
      {0, {0, 0, 0, 0, 9999, 9999}},
      {1, {1, 3, 0.2, 0.3, 3, 5}},
      {2, {2, 5, 0.275, 0.35, 2.5, 4.5}},
      {3, {4, 8, 0.35, 0.4, 2.25, 4}},
      {4, {6, 12, 0.425, 0.45, 2, 3.75}},
      {5, {10, 20, 0.5, 0.5, 1.75, 3.5}}};

  int goldDrop;
  float bounceRefund;
  float qCharge;
  float spawnDelay;

public:
  /**
   * Krug constructor.
   *
   * @param level the level to generate the Krug's stats from
   */
  Krug(std::pair<int, int> position_ = {0, 0}, int level = 0);

  /**
   * Get the time to wait before spawning the next Krug.
   *
   * @return the delay (in seconds)
   */
  float getSpawnDelay();

  /**
   * Kill the Krug and add drops to resources.
   *
   * @param[out] gold the total gold to add the dropped gold to
   * @param[out] chargesQ the total q charges to add more charge to
   * @param[out] bouncesRemaining the total bounces remaining to add more bounces to
   */
  void kill(int &gold, float &chargesQ, float &bouncesRemaining);
};

#endif // KRUG_H
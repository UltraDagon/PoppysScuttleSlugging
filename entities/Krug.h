#ifndef KRUG_H
#define KRUG_H

#include <random>
#include "Entity.h"

class Krug : public Entity
{
private:
  struct
  {
    const int minGoldDrop[6] = {0, 1, 2, 4, 6, 10};
    const int maxGoldDrop[6] = {0, 3, 5, 8, 12, 20};
    const float bounceRefund[6] = {0, 0.2, 0.275, 0.35, 0.425, 0.5};
    const float qCharge[6] = {0, 0.3, 0.35, 0.4, 0.45, 0.5};
    /// The minimum delay possible before spawning the next Krug (in seconds).
    const float spawnDelayMin[6] = {9998, 3, 2.5, 2.25, 2, 1.75};
    /// The maximum delay possible before spawning the next Krug (in seconds).
    const float spawnDelayMax[6] = {9999, 5, 4.5, 4, 3.75, 3.5};
  } LevelStats;

  int goldDrop = 0;
  float bounceRefund = 0;
  float qCharge = 0;
  float spawnDelay = 9999;
  std::pair<float, float> velocity = {0, 0};

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

  void physicsStep(float &deltaTime);

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
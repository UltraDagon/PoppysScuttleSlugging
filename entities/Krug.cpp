#include "Krug.h"

Krug::Krug(std::pair<int, int> position_, int level)
{
  size = {50, 50};
  animationData = {{128, 128}, 3, 0, 2, 0};
  spriteSheet = "krug.bmp";

  position = position_;
  position.second -= size.second / 2;

  // Left or right with speed 10 - 30 pixels per second
  velocity.first = (10 + rand() % 20) * (2 * (rand() % 2) - 1);
  // Change animation based on movement direction
  animationData.animation = (velocity.first < 0);

  bounceRefund = LevelStats.bounceRefund[level];
  qCharge = LevelStats.qCharge[level];
  goldDrop = LevelStats.minGoldDrop[level] + rand() % (LevelStats.maxGoldDrop[level] - LevelStats.minGoldDrop[level] + 1);
  spawnDelay = LevelStats.spawnDelayMin[level] + (LevelStats.spawnDelayMax[level] - LevelStats.spawnDelayMin[level]) * ((float)rand() / (float)RAND_MAX);
}

float Krug::getSpawnDelay()
{
  return spawnDelay;
}

void Krug::physicsStep(float &deltaTime)
{
  updateAnimation(deltaTime);
  position.first += velocity.first * deltaTime;
  position.second += velocity.second * deltaTime;
}

void Krug::kill(int &gold, float &chargesQ, float &bouncesRemaining)
{
  gold += goldDrop;
  chargesQ += qCharge;
  bouncesRemaining += bounceRefund;
}
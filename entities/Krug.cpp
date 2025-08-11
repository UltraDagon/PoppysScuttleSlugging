#include "Krug.h"

Krug::Krug(std::pair<int, int> position_, int level)
{
  LevelStats stats = krugLevels.at(level);
  size = {50, 50};

  position = position_;
  position.second -= size.second / 2;

  // Left or right with speed 10 - 30 pixels per second
  velocity.first = (10 + rand() % 20) * (2 * (rand() % 2) - 1);

  bounceRefund = stats.bounceRefund;
  qCharge = stats.qCharge;
  goldDrop = stats.minGoldDrop + rand() % (stats.maxGoldDrop - stats.minGoldDrop + 1);
  spawnDelay = stats.spawnDelayMin + (stats.spawnDelayMax - stats.spawnDelayMin) * ((float)rand() / (float)RAND_MAX);
}

float Krug::getSpawnDelay()
{
  return spawnDelay;
}

void Krug::physicsStep(float &deltaTime)
{
  position.first += velocity.first * deltaTime;
  position.second += velocity.second * deltaTime;
}

void Krug::kill(int &gold, float &chargesQ, float &bouncesRemaining)
{
  gold += goldDrop;
  chargesQ += qCharge;
  bouncesRemaining += bounceRefund;
}
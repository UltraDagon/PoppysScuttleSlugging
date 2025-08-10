#include "Krug.h"

Krug::Krug(std::pair<int, int> position_, int level)
{
  LevelStats stats = krugLevels.at(level);
  size = {50, 50};

  position = position_;
  position.second -= size.second / 2;

  bounceRefund = stats.bounceRefund;
  qCharge = stats.qCharge;
  goldDrop = stats.minGoldDrop + rand() % (stats.maxGoldDrop - stats.minGoldDrop + 1);
  spawnDelay = stats.spawnDelayMin + (stats.spawnDelayMax - stats.spawnDelayMin) * ((float)rand() / (float)RAND_MAX);

  std::cout << "Spawned Krug at " << position.first << ", " << position.second << std::endl;
}

float Krug::getSpawnDelay()
{
  return spawnDelay;
}

void Krug::physicsStep(float &deltaTime)
{
}

void Krug::kill(int &gold, float &chargesQ, float &bouncesRemaining)
{
  gold += goldDrop;
  chargesQ += qCharge;
  bouncesRemaining += bounceRefund;
}
#ifndef SCUTTLECRAB_H
#define SCUTTLECRAB_H

#include "Entity.h"

class ScuttleCrab : public Entity
{
public:
  bool active;
  float bouncesRemaining;
  float verticalPower;
  std::pair<float, float> velocity;

  // Upgradeable stats (maybe make this a map?)
  float airResistance;
  float minimumSpeed; // maybe rename to minHorizVelocity

public:
  ScuttleCrab();

  // Sprite *getSprite(ImageCache *images);

  void physicsStep(float &deltaTime);
};

#endif
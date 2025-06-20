#ifndef ENTITY_H
#define ENTITY_H

#include "Sprite.h"
#include "Renderer.h"

#include <utility>

const int WORLD_FLOOR_Y = 700;
const int WORLD_GRAVITY = 100; // World gravity in pixels per second^2

class Entity
{
public:
  std::pair<float, float> position;
  std::pair<int, int> size;

  Entity();

  Entity(std::pair<float, float> position_, std::pair<int, int> size_);
};

class ScuttleCrab : public Entity
{
public:
  float health;
  float verticalPower;
  std::pair<float, float> velocity;

public:
  ScuttleCrab();

  Sprite *getSprite(ImageCache *images); // I think this is actually an entity function since all entities should have their own sprites. not sure if im able to make functions have different definitions based on child

  virtual void physicsStep(float deltaTime); // Overrides Shape::physicsStep()
};

#endif // ENTITY_H

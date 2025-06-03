#ifndef ENTITY_H
#define ENTITY_H

#include "Sprite.h"
#include "Renderer.h"

#include <utility>

class Entity
{
private:
  std::pair<float, float> position;
  std::pair<float, float> velocity;

public:
  Entity();
};

class ScuttleCrab : public Entity
{
public:
  float health;

public:
  ScuttleCrab();

  Sprite *getSprite(ImageCache *images); // I think this is actually an entity function since all entities should have their own sprites. not sure if im able to make functions have different definitions based on child
};

#endif // ENTITY_H

#ifndef ENTITY_H
#define ENTITY_H

#include "Sprite.h"
#include "Renderer.h"

#include <utility>

const int WORLD_FLOOR_Y = 350;
const int WORLD_GRAVITY = 100; // World gravity in pixels per second^2

class Entity
{
public:
  std::pair<float, float> position;
  std::pair<int, int> size;

  Entity();

  Entity(std::pair<float, float> position_, std::pair<int, int> size_);

  Sprite *getSprite(ImageCache *images); // I think this should be a virtual function or something
};

class ScuttleCrab : public Entity
{
public:
  float health;
  float bouncesRemaining;
  float verticalPower;
  std::pair<float, float> velocity;

  // Upgradeable stats (maybe make this a map?)
  float airResistance;
  float minimumSpeed; // maybe rename to minHorizVelocity

public:
  ScuttleCrab();

  Sprite *getSprite(ImageCache *images); // I think this is actually an entity function since all entities should have their own sprites. not sure if im able to make functions have different definitions based on child

  void physicsStep(float deltaTime); // Overrides Shape::physicsStep()
};

/**
 * Environment objects are entities used to render the environment.
 */
class Environment : public Entity
{
private:
  /**
   * Parralax is the rate at which the sprite moves relative to the camera. (0 to 1)
   * 0: The object is close to the camera. When the camera moves, the object moves on the screen.
   * 1: The object is far from the camera. When the camera moves, the object remains still on the screen.
   */
  float parallax;

public:
  Environment();

  Environment(std::pair<float, float> position_, std::pair<int, int> size_, float parallax_);

  /**
   * @return All sprites needed to render an x-axis repeating environment texture
   */
  std::vector<Sprite *> getSprites(ImageCache *images, Renderer &renderer);
};

#endif // ENTITY_H

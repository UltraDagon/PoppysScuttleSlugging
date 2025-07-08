#ifndef ENTITY_H
#define ENTITY_H

#include "Sprite.h"
#include "Renderer.h"

#include <utility>
#include <memory>

const int WORLD_FLOOR_Y = 350;
const int WORLD_GRAVITY = 100; // World gravity in pixels per second^2

class Entity // Idk if I should get rid of this or not, the only thing each child is inheriting is the position and size.
{
public:
  std::pair<float, float> position;
  std::pair<int, int> size;
  std::string spriteSheet;

  Entity();

  Entity(std::pair<float, float> position_, std::pair<int, int> size_);

  virtual Sprite *getSprite(ImageCache *images); // I think this should be a virtual function or something
};

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

class Poppy : public Entity
{
public:
  char stage; // #: Runing between stages, W: Steadfast Presence stage (spam w to charge), E: Heroic Charge stage (quick time press e at the right moment), S: Scuttle Stage (No action)
  int scoreW; // TODO: need the input handler to interact directly with poppy to get these scores
  float betweenStageDelay;
  ScuttleCrab *crab;

public:
  Poppy();

  ~Poppy();

  void stageStep(float &deltaTime, Camera &camera);

  // void stageRunStep(float &deltaTime); // if stagestep is too big then split into smaller functions

  // Todo: if optimizing for performance, it would probably be better to just give poppy a pointer to the camera
  void hitScuttleCrab(Camera &camera);
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
  float parallax; // Todo: implement

public:
  Environment();

  Environment(std::pair<float, float> position_, std::pair<int, int> size_, float parallax_);

  /**
   * @return All sprites needed to render an environment texture that is repeating on the x-axis
   */
  std::vector<Sprite *> getSprites(ImageCache *images, Renderer &renderer);
};

#endif // ENTITY_H

#ifndef ENTITY_H
#define ENTITY_H

#include "../Sprite.h"
#include "../Renderer.h"

#include <utility>
#include <memory>
#include <cmath>

const int WORLD_FLOOR_Y = 350;
const int WORLD_GRAVITY = 100; // World gravity in pixels per second^2

class Entity // Idk if I should get rid of this or not, the only thing each child is inheriting is the position and size.
{
public:
  std::pair<float, float> position;
  std::pair<int, int> size;
  std::string spriteSheet;
  struct
  {
    std::pair<int, int> frameSize;
    int totalFrames = 1;
    int animation = 0; // Which animation is playing. If negative, don't render entity
    float speed = 1;   // Frames per second
    float currentFrame = 0;
  } animationData;

  Entity();

  virtual Sprite *getSprite(ImageCache *images); // I think this should be a virtual function or something

  void updateAnimation(float &deltaTime);
};

#endif // ENTITY_H

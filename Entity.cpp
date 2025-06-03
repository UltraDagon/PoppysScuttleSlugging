#include "Entity.h"

Entity::Entity()
{
  position = {0.0f, 0.0f};
}

ScuttleCrab::ScuttleCrab()
{
  health = 100.0f;
}

Sprite *ScuttleCrab::getSprite(ImageCache *images)
{
  return new Sprite(100, 200, 50, 100, "assets/image.bmp", images);
}
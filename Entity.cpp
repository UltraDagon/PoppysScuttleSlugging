#include "Entity.h"

Entity::Entity()
{
  position = {0.0f, 0.0f};
  size = {100, 100};
}

Entity::Entity(std::pair<float, float> position_, std::pair<int, int> size_)
{
  position = position_;
  size = size_;
}

ScuttleCrab::ScuttleCrab()
{
  health = 100.0f;
  verticalPower = 100.0f; // TODO: Rename to something else
}

Sprite *ScuttleCrab::getSprite(ImageCache *images)
{
  return new Sprite(100, position.second, size.first / 2, size.second, "assets/image.bmp", images);
}

void ScuttleCrab::physicsStep(float deltaTime)
{
  position.second += velocity.second * deltaTime;
  velocity.second += WORLD_GRAVITY * deltaTime;

  if (position.second >= WORLD_FLOOR_Y) // Hit the ground?
  {
    verticalPower -= 10;
    position.second = WORLD_FLOOR_Y;
    velocity.second = -1 * verticalPower; // pixels per second^2 // TODO: This is not done! Should scale with more things
  }
}
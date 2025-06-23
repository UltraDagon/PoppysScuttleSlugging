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

Sprite *Entity::getSprite(ImageCache *images)
{
  return new Sprite(position.first, position.second, size.first, size.second, "assets/image.bmp", images);
}

ScuttleCrab::ScuttleCrab() // TODO: Make non-default constructor so everything can be managed from GameScene.cpp
{
  health = 100.0f; // Maybe combine health with bouncesRemaining?
  bouncesRemaining = 10.0f;
  verticalPower = 100.0f; // 20.0f
}

Sprite *ScuttleCrab::getSprite(ImageCache *images)
{
  return new Sprite(position.first, position.second, size.first, size.second, "assets/image.bmp", images);
}

void ScuttleCrab::physicsStep(float deltaTime)
{
  position.second += velocity.second * deltaTime;
  velocity.second += WORLD_GRAVITY * deltaTime;

  if (position.second + size.second / 2 >= WORLD_FLOOR_Y) // Hit the ground?
  {
    bouncesRemaining -= 1;
    position.second = WORLD_FLOOR_Y - size.second / 2;
    velocity.second = -1 * bouncesRemaining * verticalPower; // pixels per second^2 // TODO: This is not done! Should scale with more things
  }

  // For enemies, if it hits below WORLD_FLOOR_Y - enemy.height, bounce with less vpower loss
}
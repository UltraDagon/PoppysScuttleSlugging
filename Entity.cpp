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
  position.first += velocity.first * deltaTime;
  position.second += velocity.second * deltaTime;
  position.first += -1 * airResistance;
  velocity.second += WORLD_GRAVITY * deltaTime;

  if (position.second + size.second / 2 >= WORLD_FLOOR_Y && bouncesRemaining > 0) // Hit the ground?
  {
    position.second = WORLD_FLOOR_Y - size.second / 2;
    velocity.second = -1 * bouncesRemaining * verticalPower; // pixels per second^2 // TODO: This is not done! Should scale with more things

    velocity.first -= (velocity.first - minimumSpeed) / bouncesRemaining;

    std::cout << "Velocity: (" << velocity.first << ", " << velocity.second << ")" << std::endl;
    bouncesRemaining -= 1;
  }

  if (velocity.first < minimumSpeed)
    velocity.first = minimumSpeed;

  // For enemies, if it hits below WORLD_FLOOR_Y - enemy.height, bounce with less vpower loss
}
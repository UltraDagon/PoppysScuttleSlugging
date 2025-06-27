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

    bouncesRemaining -= 1;
  }

  if (velocity.first < minimumSpeed)
    velocity.first = minimumSpeed;

  // For enemies, if it hits below WORLD_FLOOR_Y - enemy.height, bounce with less vpower loss
}

Environment::Environment()
{
  parallax = 0;
}

/**
 * TODO: Finish
 * Note that for environments, position.first is the offset of the image used rather than the starting x position, as the image should repeat along the x axis infinitely
 */
Environment::Environment(std::pair<float, float> position_, std::pair<int, int> size_, float parallax_)
{
  position = position_;
  size = size_;
  parallax = parallax_;
}

std::vector<Sprite *> Environment::getSprites(ImageCache *images, Renderer &renderer)
{
  std::vector<Sprite *> output;
  // These
  int startPos = -1 * ceil((0.5 * renderer.getWindowWidth() - renderer.getCameraPos().first) / size.first) * size.first + size.first / 2;
  int endPos = ceil((0.5 * renderer.getWindowWidth() + renderer.getCameraPos().first) / size.first) * size.first + size.first / 2;

  for (int xPos = startPos; xPos < endPos; xPos += size.first)
  {
    output.push_back(new Sprite((int)position.first % size.first + xPos, position.second, size.first, size.second, "assets/image.bmp", images));
  }

  return output;
}
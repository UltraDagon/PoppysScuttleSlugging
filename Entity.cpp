#include "Entity.h"

Entity::Entity()
{
  position = {0.0f, 0.0f};
  size = {100, 100};
  spriteSheet = "image.bmp";
}

Entity::Entity(std::pair<float, float> position_, std::pair<int, int> size_)
{
  position = position_;
  size = size_;
}

Sprite *Entity::getSprite(ImageCache *images)
{
  return new Sprite(position.first, position.second, size.first, size.second, "assets/" + spriteSheet, images);
}

ScuttleCrab::ScuttleCrab()
{
  size = {75, 75};
  active = false;
  position = {0, WORLD_FLOOR_Y - size.second / 2};
}

/*Sprite *ScuttleCrab::getSprite(ImageCache *images)
{
  return new Sprite(position.first, position.second, size.first, size.second, "assets/image.bmp", images);
}*/

void ScuttleCrab::physicsStep(float &deltaTime)
{
  if (!active) // If the scuttle crab is not active, don't move.
    return;

  if (bouncesRemaining == 0)
  {
    // Slide animation
    return;
  }

  position.first += velocity.first * deltaTime;
  position.second += velocity.second * deltaTime;
  velocity.first += -1 * airResistance;
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

Poppy::Poppy()
{
  position = {-300, WORLD_FLOOR_Y - size.second / 2};
  betweenStageDelay = 3; // In seconds TODO: maybe make a setting
  stage = '0';
  scoreW = 0;
}

Poppy::~Poppy()
{
  delete crab;
}

void Poppy::stageStep(float &deltaTime, Camera &camera)
{
  switch (stage)
  {
  // Stage 0: Run for betweenStageDelay seconds before starting the next stage.
  case '0':
    // Position goes down by distanceToScuttle * dt / delayRemaining, so pushing the scuttle back by performing well in the pre-round minigames will make poppy run faster, since it'll be going the same percent just over a longer distance
    position.first += abs(position.first + size.first / 2 - crab->position.first + crab->size.first / 2) * deltaTime / betweenStageDelay;

    betweenStageDelay -= deltaTime;

    // At the end of stage 0
    if (betweenStageDelay < 0)
    {
      // Hit the scuttle crab
      hitScuttleCrab(camera);
      stage = 'S';
    }
    break;
  case 'S':
    // Scuttle crab is flying!
    break;
  default:
    stage = '0';
  }
}

void Poppy::hitScuttleCrab(Camera &camera)
{
  crab->bouncesRemaining = 10.0f;
  crab->verticalPower = 20.0f; // 20.0f
  crab->airResistance = 0;
  crab->minimumSpeed = 10;
  crab->velocity.first = 100;
  crab->active = true;

  camera.transition(std::pair<int, int>{position.first - crab->position.first, position.second - crab->position.second}, 2);
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
  // These work by finding the amount of widths needed to reach the left side and right side of the screen from the center (screenWidth/2), then rounding up, then multiplying by the size of the widths, then removing the offset caused by the entity's position being their center
  int startPos = -1 * ceil((0.5 * renderer.getWindowWidth() - renderer.getCameraPos().first) / size.first) * size.first + size.first / 2;
  int endPos = ceil((0.5 * renderer.getWindowWidth() + renderer.getCameraPos().first) / size.first) * size.first + size.first / 2;

  for (int xPos = startPos; xPos < endPos; xPos += size.first)
  {
    output.push_back(new Sprite((int)position.first % size.first + xPos, position.second, size.first, size.second, "assets/image.bmp", images));
  }

  return output;
}
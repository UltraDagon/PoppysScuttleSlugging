#include "Poppy.h"

Poppy::Poppy()
{
  position = {-300, WORLD_FLOOR_Y - size.second / 2};
  size = {125, 100};
  betweenStageDelay = 3; // In seconds TODO: maybe make a setting
  stage = '0';
  scoreW = 0;
  spriteSheet = "Poppy.bmp";
  animationData.frameSize = {320, 256};
  animationData.totalFrames = 8;
  animationData.speed = 4;
}

Poppy::~Poppy()
{
  crab = nullptr; // I don't think this is needed
}

void Poppy::stageStep(float &deltaTime, Camera &camera)
{
  updateAnimation(deltaTime);

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

// Todo: if optimizing for performance, it would probably be better to just give poppy a pointer to the camera
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
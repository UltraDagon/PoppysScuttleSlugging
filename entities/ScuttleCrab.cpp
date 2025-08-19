#include "ScuttleCrab.h"

ScuttleCrab::ScuttleCrab()
{
  bouncesRemaining = 1; // Must not be 0 otherwise end screen will randomly appear too early.
  size = {75, 75};
  active = false;
  position = {0, hitboxThinning + WORLD_FLOOR_Y - size.second / 2};
  animationData = {{142, 142}, 8, 0, 0, 0};
  spriteSheet = "scuttle_crab.bmp";
}

void ScuttleCrab::physicsStep(float &deltaTime)
{
  updateAnimation(deltaTime);

  if (!active || bouncesRemaining <= 0) // If the scuttle crab is not active or has run out of bounces, don't move.
  {
    animationData.speed = 0;
    return;
  }

  position.first += velocity.first * deltaTime;
  position.second += velocity.second * deltaTime;
  // velocity.first += -1 * airResistance; // TODO: make this match description in scuttlecrab.h
  velocity.second += WORLD_GRAVITY * deltaTime;

  // Hit the ground? // Todo: can move to bounce() if need space
  if (position.second - hitboxThinning + size.second / 2 > WORLD_FLOOR_Y && bouncesRemaining > 0)
  {
    bounce();
    return;
  }

  if (velocity.first < minimumSpeed)
    velocity.first = minimumSpeed;

  // For enemies, if it hits below WORLD_FLOOR_Y - enemy.height, bounce with less vpower loss
}

void ScuttleCrab::bounce()
{
  position.second = hitboxThinning + WORLD_FLOOR_Y - size.second / 2;

  velocity.second = -1 * (bouncesRemaining / totalBounces) * verticalPower; // pixels per second^2 // TODO: This is not done! Should scale with more things
  velocity.first = (horizontalPower - minimumSpeed) * (bouncesRemaining / totalBounces) + minimumSpeed;

  bouncesRemaining -= 1;
}

void ScuttleCrab::abilityQ()
{
  if (velocity.second >= 900 || chargesQ < 1) // If downwards velocity is too high or no charges don't use Q ability
    return;

  velocity.first = minimumSpeed;
  velocity.second = 1000;
  bouncesRemaining += 0.5;
  chargesQ -= 1;
}
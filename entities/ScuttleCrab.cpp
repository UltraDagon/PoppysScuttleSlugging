#include "ScuttleCrab.h"

ScuttleCrab::ScuttleCrab()
{
  bouncesRemaining = 1; // Must not be 0 otherwise end screen will randomly appear too early.
  size = {75, 75};
  active = false;
  position = {0, WORLD_FLOOR_Y - size.second / 2};
}

void ScuttleCrab::physicsStep(float &deltaTime)
{
  updateAnimation(deltaTime);

  if (!active) // If the scuttle crab is not active, don't move.
    return;

  if (bouncesRemaining == 0)
  {
    // Slide animation
    return;
  }

  position.first += velocity.first * deltaTime;
  position.second += velocity.second * deltaTime;
  // velocity.first += -1 * airResistance; // TODO: make this match description in scuttlecrab.h
  velocity.second += WORLD_GRAVITY * deltaTime;

  // Hit the ground?
  if (position.second + size.second / 2 > WORLD_FLOOR_Y && bouncesRemaining > 0)
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

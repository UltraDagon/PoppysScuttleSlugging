#ifndef SCUTTLECRAB_H
#define SCUTTLECRAB_H

#include "Entity.h"

/// The Scuttle Crab is the main Entity followed during GameScene.
class ScuttleCrab : public Entity
{
public:
  /// Reduces the hitbox of the ScuttleCrab by this many pixels on each side
  const int hitboxThinning = 16;
  /// Whether or not the ScuttleCrab should be updated during the GameScene's physicsStep.
  bool active;
  /// How many bounces remain until the end screen appears.
  float bouncesRemaining;
  /// Determines how high the ScuttleCrab will bounce
  float verticalPower;
  /// The velocity of the ScuttleCrab, in pixels per second^2
  std::pair<float, float> velocity;

  // Upgradeable stats (maybe make this a map?)
  /// The Scuttle Crab's distance traveled is multiplied by (1 - airResistance).
  float airResistance;
  /**
   * The minimum horizontal velocity that the ScuttleCrab can reach.
   *
   * Effects the speed calculated at the start of each bounce.
   */
  float minimumSpeed;

public:
  /// ScuttleCrab constructor.
  ScuttleCrab();

  // Sprite *getSprite(ImageCache *images);

  /**
   * Progress the physics of the ScuttleCrab each frame.
   *
   * @param deltaTime the time that has elapsed since the previous frame
   */
  void physicsStep(float &deltaTime);
};

#endif
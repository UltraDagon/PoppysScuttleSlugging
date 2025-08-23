#ifndef POPPY_H
#define POPPY_H

#include "ScuttleCrab.h"
// #include "Entity.h" // Included by ScuttleCrab.h

/// Poppy is the player-controlled entity used to launch the ScuttleCrab entity at the beginning of each GameScene.
class Poppy : public Entity
{
public:
  /**
   * The current stage Poppy is progressing through.
   *
   * '#'(0 to 3): Running between stages.
   * 'W'/Steadfast Presence stage: Spam W to charge and build speed.
   * 'E'/Heroic Charge stage: Quick time event, press E at the right moment to hit with more power.
   * 'P'/Targon Buckler stage: Quick time event, press P at the right time 3 times to lock in and hit a second but weaker time.
   * 'S'/Scuttle Crab stage: No action, the scuttle is flying.
   */
  char stage;
  /**
   * How many W presses have occured during the 'W'/Steadfast Presence stage.
   *
   * Used to calculate the Scuttle Crab's overall distance traveled.
   */
  int scoreW; // TODO: need the input handler to interact directly with poppy to get these scores
  /// The delay remaining between stages.
  float betweenStageDelay;
  /// Pointer to the Scuttle Crab that Poppy hits.
  ScuttleCrab *crab;

  struct
  {
    int level = 0;
    const int bounces[6] = {3, 5, 7, 9, 11, 13};
    const int baseMaxHeight[6] = {150, 290, 430, 570, 710, 850};
    const int horizontalPower[6] = {125, 180, 235, 290, 345, 400};
  } RLevelStats;

public:
  /// Poppy constructor.
  Poppy();

  /// Poppy deconstructor.
  ~Poppy();

  /**
   * Updates Poppy's stats to match the levels provided.
   *
   * @param RLevel Poppy's R (Keeper's Verdict) level
   */
  void updateLevels(int RLevel);

  /**
   * Progress through Poppy's stages and events.
   *
   * @param deltaTime the time that has elapsed since the previous frame
   * @param camera the Camera used to render the world
   */
  void stageStep(float &deltaTime, Camera &camera);

  // void stageRunStep(float &deltaTime); // if stagestep is too big then split into smaller functions

  /**
   * Hit the Scuttle Crab and update it's variables.
   *
   * @param camera the Camera used to render the world
   */
  void hitScuttleCrab(Camera &camera);
};

#endif
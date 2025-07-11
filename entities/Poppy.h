#ifndef POPPY_H
#define POPPY_H

#include "ScuttleCrab.h"
// #include "Entity.h" // Included by ScuttleCrab.h

class Poppy : public Entity
{
public:
  char stage; // #: Runing between stages, W: Steadfast Presence stage (spam w to charge), E: Heroic Charge stage (quick time press e at the right moment), S: Scuttle Stage (No action)
  int scoreW; // TODO: need the input handler to interact directly with poppy to get these scores
  float betweenStageDelay;
  ScuttleCrab *crab;

public:
  Poppy();

  ~Poppy();

  void stageStep(float &deltaTime, Camera &camera);

  // void stageRunStep(float &deltaTime); // if stagestep is too big then split into smaller functions

  // Todo: if optimizing for performance, it would probably be better to just give poppy a pointer to the camera
  void hitScuttleCrab(Camera &camera);
};

#endif
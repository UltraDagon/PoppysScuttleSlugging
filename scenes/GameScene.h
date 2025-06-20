#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "../Entity.h"
#include "../Renderer.h"
#include "../ImageCache.h"

class GameScene
{
private:
  ScuttleCrab scuttleCrab;
  Entity floor;

public:
  GameScene();

  //~GameScene();

  void render(Renderer &renderer);

  void physicsStep(float deltaTime);
};

#endif

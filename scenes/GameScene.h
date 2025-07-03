#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "../Entity.h"
#include "../Renderer.h"
#include "../ImageCache.h"

class GameScene
{
private:
  ScuttleCrab scuttleCrab;
  Poppy poppy;
  Environment floor; // TODO: Rename (or dont)

public:
  GameScene();

  //~GameScene();

  void render(Renderer &renderer);

  void physicsStep(float deltaTime);
};

#endif

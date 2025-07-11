#ifndef GAMESCENE_H
#define GAMESCENE_H

// #include "../entities/Entity.h" // Included by ScuttleCrab.h
// #include "../entities/ScuttleCrab.h" // Included by Poppy.h
#include "../entities/Poppy.h"
#include "../entities/Environment.h"

// #include "../ImageCache.h" // Included by Sprite.h included by Renderer.h
#include "../Renderer.h"

class GameScene
{
private:
  ScuttleCrab scuttleCrab;
  Poppy poppy;
  Environment floor;

public:
  GameScene();

  ~GameScene();

  void render(Renderer &renderer);

  void physicsStep(float deltaTime, Camera &camera);
};

#endif

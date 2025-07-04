#include "GameScene.h"

#include <iostream>

GameScene::GameScene() // Lot of debugging can be done here
{
  floor = Environment(std::pair<float, float>{0, WORLD_FLOOR_Y + 15}, std::pair<int, int>{200, 30}, 0);
  // floor = Entity(std::pair<float, float>{0, 0}, std::pair<int, int>{100, 900});
  poppy.crab = &scuttleCrab;
}

void GameScene::render(Renderer &renderer)
{
  switch (poppy.stage)
  {
  case 'S':
    renderer.focusCameraLeft(scuttleCrab.position);
    break;
  default:
    renderer.focusCameraLeft(poppy.position);
  }

  for (Sprite *s : floor.getSprites(renderer.getImageCache(), renderer))
    renderer.addSprite(s);

  renderer.addSprite(scuttleCrab.getSprite(renderer.getImageCache()));
  renderer.addSprite(poppy.getSprite(renderer.getImageCache())); // Maybe dont render poppy if out of frame? It probably won't effect performance too much
}

void GameScene::physicsStep(float deltaTime)
{
  poppy.stageStep(deltaTime);
  scuttleCrab.physicsStep(deltaTime);
}
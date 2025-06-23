#include "GameScene.h"

#include <iostream>

GameScene::GameScene()
{
  floor = Entity(std::pair<float, float>{0, WORLD_FLOOR_Y + 15}, std::pair<int, int>{200, 30});
  // floor = Entity(std::pair<float, float>{0, 0}, std::pair<int, int>{100, 900});
  std::cout << scuttleCrab.health << std::endl;
  scuttleCrab.size.first = 50;
}

void GameScene::render(Renderer &renderer)
{
  renderer.focusCameraLeft(scuttleCrab.position);
  renderer.addSprite(scuttleCrab.getSprite(renderer.getImageCache()));
  renderer.addSprite(floor.getSprite(renderer.getImageCache()));
}

void GameScene::physicsStep(float deltaTime)
{
  scuttleCrab.physicsStep(deltaTime);
}
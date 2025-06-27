#include "GameScene.h"

#include <iostream>

GameScene::GameScene() // Lot of debugging can be done here
{
  floor = Environment(std::pair<float, float>{0, WORLD_FLOOR_Y + 15}, std::pair<int, int>{200, 30}, 0);
  // floor = Entity(std::pair<float, float>{0, 0}, std::pair<int, int>{100, 900});
  std::cout << scuttleCrab.health << std::endl;
  scuttleCrab.size.first = 50;
  scuttleCrab.airResistance = 0;
  scuttleCrab.minimumSpeed = 10;
  scuttleCrab.velocity.first = 100;
}

void GameScene::render(Renderer &renderer)
{
  renderer.focusCameraLeft(scuttleCrab.position);

  for (Sprite *s : floor.getSprites(renderer.getImageCache(), renderer))
    renderer.addSprite(s);

  renderer.addSprite(scuttleCrab.getSprite(renderer.getImageCache()));
}

void GameScene::physicsStep(float deltaTime)
{
  scuttleCrab.physicsStep(deltaTime);
}
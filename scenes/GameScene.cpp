#include "GameScene.h"

#include <iostream>

GameScene::GameScene() // Lot of debugging can be done here
{
  floor = Environment(std::pair<float, float>{0, WORLD_FLOOR_Y + 15}, std::pair<int, int>{200, 30}, 0);
  // floor = Entity(std::pair<float, float>{0, 0}, std::pair<int, int>{100, 900});
  poppy.crab = &scuttleCrab;
}

GameScene::~GameScene()
{
  std::cout << "Destroyed gamescene" << std::endl;
}

void GameScene::render(Renderer &renderer)
{
  if (poppy.stage == 'S') // Focus camera on the scuttle crab when it is flying
    renderer.focusCameraLeft(scuttleCrab.position);
  else // Otherwise, focus the camera on Poppy
    renderer.focusCameraLeft(poppy.position);

  // Print horizontal expanding environment entities
  for (Sprite *s : floor.getSprites(renderer.getImageCache(), renderer))
    renderer.addSprite(s);

  renderer.addSprite(scuttleCrab.getSprite(renderer.getImageCache()));
  renderer.addSprite(poppy.getSprite(renderer.getImageCache())); // Maybe dont render poppy if out of frame? It probably won't effect performance too much
}

void GameScene::physicsStep(float deltaTime, Camera &camera)
{
  poppy.stageStep(deltaTime, camera);
  scuttleCrab.physicsStep(deltaTime);
}
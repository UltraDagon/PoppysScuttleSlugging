#include "GameScene.h"

#include <iostream>

GameScene::GameScene()
{
  std::cout << scuttleCrab.health << std::endl;
}

void GameScene::render(Renderer &renderer)
{
  renderer.addSprite(scuttleCrab.getSprite(renderer.getImageCache()));
}
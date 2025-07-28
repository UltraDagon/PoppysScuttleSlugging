#include "MainMenuScene.h"

MainMenuScene::MainMenuScene(ResourceManager &resManager)
{
  resourceManager = &resManager;
}

void MainMenuScene::render(Renderer &renderer)
{
  UIElement gameTitle({0, -200}, {1200, 500}, "Poppy.bmp");

  renderer.addSprite(gameTitle.getSprite(renderer.getImageCache()));
}

void MainMenuScene::physicsStep(InputHandler &input, Renderer &renderer)
{
}
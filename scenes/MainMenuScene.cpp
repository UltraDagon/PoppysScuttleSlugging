#include "MainMenuScene.h"

MainMenuScene::MainMenuScene(ResourceManager &resManager)
{
  resourceManager = &resManager;
}

void MainMenuScene::render(Renderer &renderer)
{
  UIElement gameTitle({0, -200}, {1200, 500}, "poppy.bmp");
  UIElement fontTest({700, 0}, {100, 800}, "default_font.bmp");
  // TextElement textPlay("PLAY GAME", {0, 0}, {900, 100});
  // TextElement testing("TESTING TEXT", {300, 0}, 64, TextElement::TextAlignment::CENTER);

  renderer.addSprite(gameTitle.getSprite(renderer.getImageCache()));
  renderer.addSprite(fontTest.getSprite(renderer.getImageCache()));
}

void MainMenuScene::physicsStep(InputHandler &input, Renderer &renderer)
{
}
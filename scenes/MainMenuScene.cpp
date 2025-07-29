#include "MainMenuScene.h"

MainMenuScene::MainMenuScene(ResourceManager &resManager)
{
  resourceManager = &resManager;
}

void MainMenuScene::render(Renderer &renderer)
{
  UIElement gameTitle({0, -200}, {1200, 500}, "poppy.bmp");
  TextElement textPlay("PLAY GAME 123's", {0, -100}, {900, 60});
  TextElement textPlay2("PLAY GAME 123's", {0, 0}, {900, 60}, 16);
  TextElement testing("PLAY GAME 123's", {0, 100}, 60, TextElement::TextAlignment::CENTER);
  TextElement testing2("PLAY GAME 123's", {0, 200}, 60, TextElement::TextAlignment::CENTER, 16);
  TextElement testing3("PLAY GAME 123's", {0, 300}, 60, TextElement::TextAlignment::LEFT, 16);
  TextElement testing4("PLAY GAME 123's", {0, 400}, 60, TextElement::TextAlignment::RIGHT, 16);

  renderer.addSprite(gameTitle.getSprite(renderer.getImageCache()));
  renderer.addSprites(textPlay.getSprites(renderer));
  renderer.addSprites(textPlay2.getSprites(renderer));
  renderer.addSprites(testing.getSprites(renderer));
  renderer.addSprites(testing2.getSprites(renderer));
  renderer.addSprites(testing3.getSprites(renderer));
  renderer.addSprites(testing4.getSprites(renderer));
}

void MainMenuScene::physicsStep(InputHandler &input, Renderer &renderer)
{
}
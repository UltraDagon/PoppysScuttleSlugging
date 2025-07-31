#include "GameScene.h"

#include <iostream>

void GameScene::renderEndPopup(Renderer &renderer)
{
  UIElement endPopup({renderer.getCameraPos().first, endPopupData.travelDistancePerSecond * endPopupData.moveInDelayRemaining}, {1200, 675}, "poppy.bmp");
  TextElement runOverText("RUN OVER", {0, 160 - endPopup.size.second / 2}, 120, TextElement::TextAlignment::CENTER, 8, &endPopup);
  TextElement distanceTraveledText("DISTANCE TRAVELED: 999M", {0, -20}, 50, TextElement::TextAlignment::CENTER, 8, &endPopup);
  TextElement goldEarnedText("GOLD EARNED: 99", {0, 80}, 50, TextElement::TextAlignment::CENTER, 8, &endPopup);
  UIElement shopButton({0, endPopup.size.second / 2 - 102}, {525, 125}, "upgrade_button.bmp", &endPopup);
  TextElement visitShopText("VISIT SHOP", {0, 0}, 60, TextElement::TextAlignment::CENTER, 8, &shopButton);

  const std::pair<int, int> shopButtonAbsPos = shopButton.absolutePosition();
  buttons["s"] = {shopButtonAbsPos.first, shopButtonAbsPos.second, shopButton.size.first, shopButton.size.second, buttons["s"].state, UIElement::ButtonType::SCENE_NAVIGATION};

  endPopup.render(renderer);
  runOverText.render(renderer);
  distanceTraveledText.render(renderer);
  goldEarnedText.render(renderer);
  shopButton.render(renderer);
  visitShopText.render(renderer);
}

void GameScene::handleButtons(InputHandler &input, Renderer &renderer)
{
  for (auto &b : buttons)
  {
    b.second.updateState(renderer.getCameraPos().first + input.mouseX - renderer.getWindowWidth() / 2, input.mouseY - renderer.getWindowHeight() / 2, input.mouseState & SDL_BUTTON_LMASK);
    if (b.second.state != 'c') // If button isn't clicked
      continue;

    // Handle the button being clicked
    switch (b.second.type)
    {
    case UIElement::ButtonType::SCENE_NAVIGATION:
      resourceManager->changeScene(b.first.at(0)); // Change scene to first char in scene name
      break;
    default:
      break;
    }
  }
}

GameScene::GameScene() // Lot of debugging can be done here
{
  floor = Environment(std::pair<float, float>{0, WORLD_FLOOR_Y + 15}, std::pair<int, int>{200, 30}, 0);
  // floor = Entity(std::pair<float, float>{0, 0}, std::pair<int, int>{100, 900});
  poppy.crab = &scuttleCrab;
}

GameScene::~GameScene()
{
}

void GameScene::render(Renderer &renderer)
{
  if (poppy.stage == 'S') // Focus camera on the scuttle crab when it is flying
    renderer.focusCameraLeft(scuttleCrab.position);
  else // Otherwise, focus the camera on Poppy
    renderer.focusCameraLeft(poppy.position);

  floor.render(renderer);
  scuttleCrab.render(renderer);
  poppy.render(renderer); // Maybe dont render poppy if out of frame? It probably won't effect performance too much
  renderEndPopup(renderer);
}

void GameScene::physicsStep(float deltaTime, InputHandler &input, Renderer &renderer)
{
  handleButtons(input, renderer);
  poppy.stageStep(deltaTime, renderer.getCamera());
  scuttleCrab.physicsStep(deltaTime);

  if (scuttleCrab.bouncesRemaining == 0 && endPopupData.moveInDelayRemaining > 0)
  {
    endPopupData.moveInDelayRemaining -= deltaTime;
    if (endPopupData.moveInDelayRemaining < 0)
      endPopupData.moveInDelayRemaining = 0;
  }
}
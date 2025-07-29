#include "ShopScene.h"

void ShopScene::renderUpgrade(int index, std::string resource, std::string name_, std::string icon_, Renderer &renderer, UIElement *parent)
{
  const int backplateSizeX = 400;
  const int backplateSizeY = 180;
  const int indexPosX = (index % 3 - 1) * parent->size.first / 3;
  const int indexPosY = (floor(index / 3) - 0.5) * parent->size.second / 2;

  UIElement backplate({indexPosX, indexPosY}, {backplateSizeX, backplateSizeY}, "poppy.bmp" /*<-- Todo: This should be a backplate image*/, parent);
  UIElement icon({120 / 2 - backplateSizeX / 2, -120 / 2 + backplateSizeY / 2}, {120, 120}, "image.bmp", &backplate);
  UIElement upgradeButton({-120 / 2 + backplateSizeX / 2, -60 / 2 + backplateSizeY / 2}, {120, 60}, "Upgrade_Button.bmp", &backplate);
  upgradeButton.animationData.frameSize = {120, 60};

  // Update button hitbox to match new position
  std::pair<int, int> upgradeButtonAbsPos = upgradeButton.absolutePosition();

  buttons[resource] = {upgradeButtonAbsPos.first, upgradeButtonAbsPos.second, upgradeButton.size.first, upgradeButton.size.second, buttons[resource].state};

  // Change upgrade button to be pressed sprite when pressed
  if (buttons[resource].state == 'p')
    upgradeButton.animationData.animation = 1;
  else
    upgradeButton.animationData.animation = 0;

  renderer.addSprite(backplate.getSprite(renderer.getImageCache()));
  renderer.addSprite(icon.getSprite(renderer.getImageCache()));
  renderer.addSprite(upgradeButton.getSprite(renderer.getImageCache()));
}

void ShopScene::handleButtons(InputHandler &input, Renderer &renderer)
{
  bool purchaseSuccess = false;
  for (auto &b : buttons)
  {
    // TODO: Fix this so it works if buttons move in the world, right now it only works if camera is @ 0,0
    b.second.updateState(input.mouseX - renderer.getWindowWidth() / 2, input.mouseY - renderer.getWindowHeight() / 2, input.mouseState & SDL_BUTTON_LMASK);
    if (b.second.state != 'c') // If button isn't clicked
      continue;

    // Handle the button being clicked
    switch (b.second.type)
    {
    case UIElement::ButtonType::UPGRADE:
      purchaseSuccess = resourceManager->purchaseUpgrade(b.first);
      std::cout << "Clicked " << b.first << "! Enough gold?: " << purchaseSuccess << std::endl;
      break;
    case UIElement::ButtonType::SCENE_NAVIGATION:
      resourceManager->changeScene(b.first.at(0)); // Change scene to first char in scene name
      break;
    default:
      break;
    }
  }
}

ShopScene::ShopScene()
{
}

ShopScene::ShopScene(ResourceManager &resManager)
{
  setResourceManager(resManager);
}

void ShopScene::render(Renderer &renderer)
{
  UIElement poppyUpgradeBoard({0, 175}, {1450, 550}, "poppy.bmp");

  renderer.addSprite(poppyUpgradeBoard.getSprite(renderer.getImageCache()));
  renderUpgrade(0, "r_level", "Keeper's Verdict", "image.bmp", renderer, &poppyUpgradeBoard);
  renderUpgrade(5, "w_level", "Steadfast Presence", "image.bmp", renderer, &poppyUpgradeBoard);
}

void ShopScene::physicsStep(float deltaTime, InputHandler &input, Renderer &renderer)
{
  handleButtons(input, renderer);
}

void ShopScene::setResourceManager(ResourceManager &resManager)
{
  resourceManager = &resManager;
}
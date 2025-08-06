#include "ShopScene.h"

void ShopScene::renderUpgrade(int index, std::string resource, std::string name_, std::string icon_, Renderer &renderer, UIElement *parent)
{
  const int backplateSizeX = 420;
  const int backplateSizeY = 200;
  const int indexPosX = (index % 3 - 1) * parent->size.first / 3;
  const int indexPosY = (floor(index / 3) - 0.5) * parent->size.second / 2;
  const int upgradeCost = resourceManager->getUpgradeCost(resource + std::to_string((int)resourceManager->getNumberResource("saveData", resource) + 1));

  std::string priceString1;
  std::string priceString2;
  if (upgradeCost != -1) // If an upgrade is available
  {
    priceString1 = "PRICE:";
    priceString2 = std::to_string(upgradeCost) + "G";
  }
  else
  {
    priceString1 = "MAX";
    priceString2 = "LVL";
  }

  UIElement backplate({indexPosX, indexPosY}, {backplateSizeX, backplateSizeY}, "metal_plate.bmp", parent);
  UIElement icon({20 + 120 / 2 - backplateSizeX / 2, -20 + -120 / 2 + backplateSizeY / 2}, {120, 120}, "image.bmp", &backplate);
  UIElement upgradeButton({-20 + -120 / 2 + backplateSizeX / 2, -20 + -60 / 2 + backplateSizeY / 2}, {120, 60}, "upgrade_button.bmp", &backplate);
  upgradeButton.animationData.frameSize = {120, 60};
  TextElement upgradeNameText(name_, {0, 36 - backplateSizeY / 2}, 27, TextElement::TextAlignment::CENTER, 8, &backplate);
  TextElement priceText1(priceString1, {-64, -63 + backplateSizeY / 2}, 27, TextElement::TextAlignment::LEFT, 8, &backplate);
  TextElement priceText2(priceString2, {-64, -32 + backplateSizeY / 2}, 27, TextElement::TextAlignment::LEFT, 8, &backplate);

  // Update button hitbox to match new position
  const std::pair<int, int> upgradeButtonAbsPos = upgradeButton.absolutePosition();
  buttons[resource] = {upgradeButtonAbsPos.first, upgradeButtonAbsPos.second, upgradeButton.size.first, upgradeButton.size.second, buttons[resource].state, UIElement::ButtonType::UPGRADE};

  // Change upgrade button to be pressed sprite when pressed
  upgradeButton.animationData.animation = (buttons[resource].state == 'p');

  // Render everything
  backplate.render(renderer);
  icon.render(renderer);
  upgradeButton.render(renderer);
  upgradeNameText.render(renderer);
  priceText1.render(renderer);
  priceText2.render(renderer);
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

ShopScene::ShopScene(ResourceManager &resManager)
{
  resourceManager = &resManager;
}

void ShopScene::render(Renderer &renderer)
{
  // Create all entities to be displayed in the frame
  UIElement poppyUpgradeBoard({0, 160}, {1550, 580}, "wooden_sign.bmp");
  poppyUpgradeBoard.animationData.frameSize = {400, 200}; // todo: Remove once poppy upgrade board image is done
  UIElement mainMenuButton({-renderer.getWindowWidth() / 2 + 100, -renderer.getWindowHeight() / 2 + 100}, {200, 200}, "wooden_sign.bmp");
  UIElement playButton({renderer.getWindowWidth() / 2 - 100, -renderer.getWindowHeight() / 2 + 100}, {200, 200}, "wooden_sign.bmp");
  TextElement playText("PLAY", {0, 0}, 50, TextElement::TextAlignment::CENTER, 8, &playButton);
  TextElement mainMenuText1("MAIN", {0, -27}, 50, TextElement::TextAlignment::CENTER, 8, &mainMenuButton);
  TextElement mainMenuText2("MENU", {0, 27}, 50, TextElement::TextAlignment::CENTER, 8, &mainMenuButton);

  // Update button data to match positions and states of buttons
  const std::pair<int, int> mainMenuButtonAbsPos = mainMenuButton.absolutePosition();
  mainMenuButton.animationData.frameSize = {400, 200};
  mainMenuButton.animationData.animation = (buttons["m"].state == 'p');
  const std::pair<int, int> playButtonAbsPos = playButton.absolutePosition();
  playButton.animationData.frameSize = {400, 200};
  playButton.animationData.animation = (buttons["g"].state == 'p');

  // Update button's hitboxes to match button's positions
  buttons["m"] = {mainMenuButtonAbsPos.first, mainMenuButtonAbsPos.second, mainMenuButton.size.first, mainMenuButton.size.second, buttons["m"].state, UIElement::ButtonType::SCENE_NAVIGATION};
  buttons["g"] = {playButtonAbsPos.first, playButtonAbsPos.second, playButton.size.first, playButton.size.second, buttons["g"].state, UIElement::ButtonType::SCENE_NAVIGATION};

  // Render everything
  poppyUpgradeBoard.render(renderer);
  renderUpgrade(0, "r_level", "Keeper's Verdict", "icon_r.bmp", renderer, &poppyUpgradeBoard);
  renderUpgrade(1, "q_level", "Hammer Shock", "icon_q.bmp", renderer, &poppyUpgradeBoard);
  renderUpgrade(2, "scuttle_defense_level", "Hardened Shell", "icon_scuttle_defense.bmp", renderer, &poppyUpgradeBoard);
  renderUpgrade(3, "krug_level", "Monster: Krug", "icon_krug.bmp", renderer, &poppyUpgradeBoard);
  renderUpgrade(4, "gold_gain_level", "Kleptomancy", "coin.bmp", renderer, &poppyUpgradeBoard);
  mainMenuButton.render(renderer);
  playButton.render(renderer);
  playText.render(renderer);
  mainMenuText1.render(renderer);
  mainMenuText2.render(renderer);
}

void ShopScene::physicsStep(float deltaTime, InputHandler &input, Renderer &renderer)
{
  handleButtons(input, renderer);
}
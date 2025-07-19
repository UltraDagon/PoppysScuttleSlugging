#include "ShopScene.h"

void ShopScene::renderUpgrade(int index, std::string resource, std::string name_, std::string icon_, Renderer &renderer, UIElement *parent)
{
  const int backplateSizeX = 400;
  const int backplateSizeY = 180;
  const int indexPosX = (index % 3 - 1) * parent->size.first / 3;
  const int indexPosY = (floor(index / 3) - 0.5) * parent->size.second / 2;

  UIElement backplate({indexPosX, indexPosY}, {backplateSizeX, backplateSizeY}, "Poppy.bmp" /*<-- Todo: This should be a backplate image*/, parent);
  UIElement icon({120 / 2 - backplateSizeX / 2, -120 / 2 + backplateSizeY / 2}, {120, 120}, "image.bmp", &backplate);
  UIElement upgradeButton({-120 / 2 + backplateSizeX / 2, -60 / 2 + backplateSizeY / 2}, {120, 60}, "image.bmp", &backplate);

  // Update button hitbox to match new position
  std::pair<int, int> upgradeButtonAbsPos = upgradeButton.absolutePosition();

  buttons[resource] = {upgradeButtonAbsPos.first, upgradeButtonAbsPos.second, upgradeButton.size.first, upgradeButton.size.second};

  renderer.addSprite(backplate.getSprite(renderer.getImageCache()));
  renderer.addSprite(icon.getSprite(renderer.getImageCache()));
  renderer.addSprite(upgradeButton.getSprite(renderer.getImageCache()));
}

ShopScene::ShopScene()
{
}

// ShopScene::ShopScene(ResourceManager *resManager){}

void ShopScene::render(Renderer &renderer)
{
  UIElement poppyUpgradeBoard({0, 175}, {1450, 550}, "Poppy.bmp");

  renderer.addSprite(poppyUpgradeBoard.getSprite(renderer.getImageCache()));
  renderUpgrade(0, "r_level", "Keeper's Verdict", "image.bmp", renderer, &poppyUpgradeBoard);
  renderUpgrade(5, "w_level", "Steadfast Presence", "image.bmp", renderer, &poppyUpgradeBoard);
}

void ShopScene::physicsStep(float deltaTime, InputHandler &input, Renderer &renderer)
{
  // std::cout << "Mouse: " << input.mouseX - renderer.getWindowWidth() / 2 << ", " << input.mouseY - renderer.getWindowHeight() / 2 << " Buttons: ";
  for (auto b : buttons)
  {
    // std::cout << b.first << "[" << b.second.x << ", " << b.second.y << ", " << b.second.w << ", " << b.second.h << "] (";
    if (b.second.x - b.second.w / 2 < input.mouseX - renderer.getWindowWidth() / 2 && input.mouseX - renderer.getWindowWidth() / 2 < b.second.x + b.second.w / 2 &&
        b.second.y - b.second.h / 2 < input.mouseY - renderer.getWindowHeight() / 2 && input.mouseY - renderer.getWindowHeight() / 2 < b.second.y + b.second.h / 2)
    {
      // Mouse is hovering button
      if (input.mouseState & SDL_BUTTON_LMASK) // Left click down
      {
        std::cout << "Clicked " << b.first << "!" << std::endl;
      }
    }
    // std::cout << ")";
  }
  std::cout << std::endl;
}

void ShopScene::setResourceManager(ResourceManager &resManager)
{
  resourceManager = &resManager;
}
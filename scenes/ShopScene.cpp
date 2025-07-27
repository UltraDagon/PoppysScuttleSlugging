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

  buttons[resource] = {upgradeButtonAbsPos.first, upgradeButtonAbsPos.second, upgradeButton.size.first, upgradeButton.size.second, buttons[resource].state};

  renderer.addSprite(backplate.getSprite(renderer.getImageCache()));
  renderer.addSprite(icon.getSprite(renderer.getImageCache()));
  renderer.addSprite(upgradeButton.getSprite(renderer.getImageCache()));
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
  UIElement poppyUpgradeBoard({0, 175}, {1450, 550}, "Poppy.bmp");

  renderer.addSprite(poppyUpgradeBoard.getSprite(renderer.getImageCache()));
  renderUpgrade(0, "r_level", "Keeper's Verdict", "image.bmp", renderer, &poppyUpgradeBoard);
  renderUpgrade(5, "w_level", "Steadfast Presence", "image.bmp", renderer, &poppyUpgradeBoard);
}

void ShopScene::physicsStep(float deltaTime, InputHandler &input, Renderer &renderer)
{
  // TODO: This is really messy (almost breaks 50 line function limit), should move to other functions. Maybe name handleButtons(std::vector<Button> &buttons) and move to UIElement.h, as it should be used in all scenes
  bool purchaseSuccess = false;
  for (auto &b : buttons)
  {
    // TODO: Fix this so it works if buttons move in the world, right now it only works if camera is @ 0,0
    if (b.second.x - b.second.w / 2 < input.mouseX - renderer.getWindowWidth() / 2 && input.mouseX - renderer.getWindowWidth() / 2 < b.second.x + b.second.w / 2 &&
        b.second.y - b.second.h / 2 < input.mouseY - renderer.getWindowHeight() / 2 && input.mouseY - renderer.getWindowHeight() / 2 < b.second.y + b.second.h / 2)
    {
      // TODO: Rewrite this to look prettier (switch case?)
      if (input.mouseState & SDL_BUTTON_LMASK) // Left click down
      {
        if (b.second.state == 'h') // Don't press if it isn't hovered first to avoid misclicks
          b.second.state = 'p';    // Button is pressed
      }
      else if (b.second.state == 'p') // If button was pressed but left click is no longer down, the button has been clicked
      {
        switch (b.second.type)
        {
        case BUTTON_UPGRADE:
          purchaseSuccess = resourceManager->purchaseUpgrade(b.first);
          std::cout << "Clicked " << b.first << "! Enough gold?: " << purchaseSuccess << std::endl;
          break;
        case BUTTON_SCENE_NAVIGATION:
          resourceManager->changeScene(b.first.at(0)); // Change scene to first char in scene name
          break;
        default:
          break;
        }
        b.second.state = 'h'; // Return to hovered
      }
      else
      {
        b.second.state = 'h'; // Button is hovered
      }
    }
    else // Mouse is not over button
    {
      b.second.state = 'd'; // Button is in default state
    }
  }
}

void ShopScene::setResourceManager(ResourceManager &resManager)
{
  resourceManager = &resManager;
}
#include "ShopScene.h"

void ShopScene::renderUpgrade(int index, std::string resource, std::string name_, std::string icon_, Renderer &renderer, UIElement *parent)
{
  const int backplateSizeX = 400;
  const int backplateSizeY = 180;
  const int indexPosX = (index % 3 - 1) * parent->size.first / 3;
  const int indexPosY = (floor(index / 3) - 0.5) * parent->size.second / 2;

  UIElement backplate({indexPosX, indexPosY}, {backplateSizeX, backplateSizeY}, "Poppy.bmp" /*<-- Todo: This should be a backplate image*/, parent);
  UIElement icon({120 / 2 - backplateSizeX / 2, -120 / 2 + backplateSizeY / 2}, {120, 120}, "image.bmp", &backplate);

  renderer.addSprite(backplate.getSprite(renderer.getImageCache()));
  renderer.addSprite(icon.getSprite(renderer.getImageCache()));
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
  renderUpgrade(5, "r_level", "Keeper's Verdict", "image.bmp", renderer, &poppyUpgradeBoard);
}

void ShopScene::setResourceManager(ResourceManager &resManager)
{
  resourceManager = &resManager;
}
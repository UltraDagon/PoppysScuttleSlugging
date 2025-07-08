#include "ShopScene.h"

ShopScene::ShopScene()
{
}

// ShopScene::ShopScene(ResourceManager *resManager){}

void ShopScene::setResourceManager(ResourceManager &resManager)
{
  resourceManager = &resManager;
}
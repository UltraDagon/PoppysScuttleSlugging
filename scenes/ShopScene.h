#ifndef SHOPSCENE_H
#define SHOPSCENE_H

#include "../Renderer.h"
#include "../ResourceManager.h"
#include "../ImageCache.h"

class ShopScene
{
public:
  ResourceManager *resourceManager;

public:
  ShopScene();

  void render(Renderer &renderer);

  void setResourceManager(ResourceManager &resManager);
};

#endif
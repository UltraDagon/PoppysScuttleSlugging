#include "scenes/GameScene.h"
#include "scenes/ShopScene.h"

#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

class SceneManager
{
private:
  char activeScene;
  std::unique_ptr<GameScene> gameScene = std::make_unique<GameScene>();
  std::unique_ptr<ShopScene> shopScene;

  ResourceManager *resourceManager;

public:
  SceneManager(char _activeScene, ResourceManager &resManager);

  ~SceneManager();

  void setScene(char _activeScene);

  void render(Renderer &renderer, InputHandler &inputHandler);
};

#endif // SCENEMANAGER_H
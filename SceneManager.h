#include "scenes/GameScene.h"
#include "scenes/ShopScene.h"

#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

class SceneManager
{
private:
  char activeScene;
  std::unique_ptr<GameScene> gameScene;
  std::unique_ptr<ShopScene> shopScene;
  /// Pointer to the Renderer that controls the window rendering and camera
  Renderer *renderer;
  /// Pointer to the ResourceManager that controls internally and externally saved resources.
  ResourceManager *resourceManager;

public:
  SceneManager(char activeScene, Renderer &renderer_, ResourceManager &resManager);

  ~SceneManager();

  char getActiveScene();

  void setScene(char activeScene_);

  void render(Renderer &renderer, InputHandler &inputHandler);
};

#endif // SCENEMANAGER_H
#include "SceneManager.h"

SceneManager::SceneManager(char activeScene_, ResourceManager &resManager)
{
  activeScene = activeScene_;
  resourceManager = &resManager;

  shopScene = std::make_unique<ShopScene>(); ////
  gameScene = std::make_unique<GameScene>(); ////

  shopScene->setResourceManager(resManager);
}

SceneManager::~SceneManager()
{
  gameScene.reset(nullptr);
  shopScene.reset(nullptr);
}

void SceneManager::setScene(char activeScene_)
{
  activeScene = activeScene_;
}

void SceneManager::render(Renderer &renderer, InputHandler &inputHandler)
{
  switch (activeScene)
  {
  case 'm':
    activeScene = 's'; // Until MainMenuScene is created, default to ShopScene
    break;
  case 's':
    shopScene->physicsStep(renderer.deltaTime(), inputHandler, renderer);
    shopScene->render(renderer);
    break;
  case 'g':
    gameScene->physicsStep(renderer.deltaTime(), renderer.getCamera());
    gameScene->render(renderer);
    break;
  default:             // If something goes wrong and the activeScene is lost,
    activeScene = 'm'; // Return to MainMenuScene
  }
}
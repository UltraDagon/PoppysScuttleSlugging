#include "SceneManager.h"

SceneManager::SceneManager(char activeScene, Renderer &renderer_, ResourceManager &resManager)
    : renderer(&renderer_), resourceManager(&resManager)
{
  setScene(activeScene);
}

SceneManager::~SceneManager()
{
  gameScene.reset(nullptr);
  shopScene.reset(nullptr);
}

char SceneManager::getActiveScene()
{
  return activeScene;
}

void SceneManager::setScene(char activeScene_)
{
  activeScene = activeScene_;

  gameScene.reset(nullptr);
  shopScene.reset(nullptr);

  renderer->getCamera().x = renderer->getCamera().x = 0;
  renderer->getCamera().zoom = 1;

  switch (activeScene)
  {
  case 'm':
    mainMenuScene = std::make_unique<MainMenuScene>(*resourceManager);
    break;
  case 's':
    shopScene = std::make_unique<ShopScene>();
    shopScene->setResourceManager(*resourceManager);
    break;
  case 'g':
    gameScene = std::make_unique<GameScene>();
    break;
  default: // Default to main menu if something goes wrong
    setScene('m');
  }
}

void SceneManager::render(Renderer &renderer, InputHandler &inputHandler)
{
  switch (activeScene)
  {
  case 'm':
    mainMenuScene->physicsStep(inputHandler, renderer);
    mainMenuScene->render(renderer);
    break;
  case 's':
    shopScene->physicsStep(renderer.deltaTime(), inputHandler, renderer);
    shopScene->render(renderer);
    break;
  case 'g':
    gameScene->physicsStep(renderer.deltaTime(), inputHandler, renderer);
    gameScene->render(renderer);
    break;
  default: // If something goes wrong and the activeScene is lost,
    setScene('m');
  }
}
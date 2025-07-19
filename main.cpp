#include "Renderer.h"
#include "InputHandler.h"
#include "ImageCache.h"
#include "Sprite.h"
#include "ResourceManager.h" // todo: Might need to move somewhere else

#include "scenes/GameScene.h"
#include "scenes/ShopScene.h"

#include <iostream>
#include <memory>

// Poppy's Scuttle Slugging was created under Riot Games's "Legal Jibber Jabber" policy using intellectual property owned by Riot Games.
// This project is not affiliated with Riot Games.

// Documentation formatted under https://developer.lsst.io/cpp/api-docs.html

// Credits (keeping here so I can remember for later)
// References for drawing characters: https://modelviewer.lol/,
// (company)'s SDL2 was used for all graphics, input, and sound.

// No code within this project was generated using artificial intelligence.

using namespace std; // Todo: remove

int main(int argc, char *argv[])
{
  cout << "Hello World!" << endl;
  bool running = true;

  Renderer renderer(1600, 900);
  ResourceManager resourceManager;

  std::unique_ptr<GameScene> gameScene = std::make_unique<GameScene>();
  std::unique_ptr<ShopScene> shopScene = std::make_unique<ShopScene>();

  InputHandler inputHandler(&running, &renderer); // Has access to renderer to change camera stuff

  while (running)
  {
    inputHandler.handleInput();

    // When switching scenes, image cache should be cleared. If possible: put this in scenehandler

    // gameScene->physicsStep(renderer.deltaTime(), renderer.getCamera());
    // gameScene->render(renderer);

    shopScene->physicsStep(renderer.deltaTime(), inputHandler, renderer);
    shopScene->render(renderer);

    renderer.update();
  }

  gameScene.reset(nullptr);
  shopScene.reset(nullptr);

  return 0;
}
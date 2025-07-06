#include "Renderer.h"
#include "InputHandler.h"
#include "ImageCache.h"
#include "Sprite.h"
#include "ResourceManager.h" // todo: Might need to move somewhere else

#include "scenes/GameScene.h"

#include <iostream>

// Poppy's Scuttle Slugging was created under Riot Games's "Legal Jibber Jabber" policy using intellectual property owned by Riot Games.
// This project is not affiliated with Riot Games in any way.

// Documentation formatted under https://developer.lsst.io/cpp/api-docs.html

// Credits (keeping here so I can remember for later)
// References for drawing characters: https://modelviewer.lol/,

using namespace std; // Todo: remove

int main(int argc, char *argv[])
{
  cout << "Hello World!" << endl;
  bool running = true;

  Renderer renderer(1600, 900);
  InputHandler inputHandler(&running, &renderer);
  ResourceManager resourceManager;

  GameScene *gameScene = new GameScene();

  while (running)
  {
    inputHandler.handleInput();

    gameScene->physicsStep(renderer.deltaTime(), renderer.getCamera());
    gameScene->render(renderer);
    renderer.update();
  }
  return 0;
}
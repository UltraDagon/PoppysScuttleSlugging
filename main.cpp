#include "Renderer.h"
#include "InputHandler.h"
#include "ImageCache.h"
#include "Sprite.h"
#include "ResourceManager.h" // todo: Might need to move somewhere else

#include "SceneManager.h"
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
  resourceManager.loadAllResources();

  InputHandler inputHandler(&running, &renderer); // Has access to renderer to change camera stuff

  SceneManager sceneManager('s', renderer, resourceManager); // Todo: should be 'm'

  while (running)
  {
    inputHandler.handleInput();

    // Switch scenes via keypress
    if (inputHandler.keysPressed['s'])
      resourceManager.changeScene('s');
    if (inputHandler.keysPressed['g'])
      resourceManager.changeScene('g');
    if (inputHandler.keysPressed['m'])
      resourceManager.changeScene('m');

    // Scenes should only switch when requested by the resource manager (to prevent header file looping) and when the new scene differs from the current one
    if (resourceManager.getNewScene() != ' ' && resourceManager.getNewScene() != sceneManager.getActiveScene())
    {
      sceneManager.setScene(resourceManager.getNewScene());
      resourceManager.changeScene(' ');
    }

    // When switching scenes, image cache should be cleared. If possible: put this in scenehandler
    sceneManager.render(renderer, inputHandler);

    renderer.update();
  }

  return 0;
}
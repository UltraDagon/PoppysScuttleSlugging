#include "Renderer.h"
#include "InputHandler.h"
#include "ImageCache.h"
#include "Sprite.h"

#include "scenes/GameScene.h"

#include <iostream>

// Documentation formatted under https://developer.lsst.io/cpp/api-docs.html

using namespace std;

int main(int argc, char *argv[])
{
  cout << "Hello World!" << endl;
  bool running = true;

  Renderer renderer(1600, 900);
  InputHandler inputHandler(&running, &renderer);

  GameScene *gameScene = new GameScene();

  while (running)
  {
    inputHandler.handleInput();
    // gameScene.physicsStep();
    // gameScene.render();
    renderer.update();
  }
  return 0;
}
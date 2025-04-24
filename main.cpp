#include <iostream>
#include "Renderer.h"
#include "InputHandler.h"
#include "ImageCache.h"
#include "Sprite.h"

using namespace std;

int main(int argc, char *argv[])
{
  cout << "Hello World!" << endl;
  bool running = true;

  Renderer renderer(1600, 900);
  InputHandler inputHandler(&running, &renderer);

  while (running)
  {
    inputHandler.handleInput();
    renderer.update();
  }
  return 0;
}
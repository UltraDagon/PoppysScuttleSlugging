#include <iostream>
#include "Renderer.h"
#include "InputHandler.h"

using namespace std;

int main(int argc, char *argv[])
{
  cout << "Hello World!" << endl;
  bool running = true;

  Renderer renderer(500, 500);
  InputHandler inputHandler(&running, &renderer);

  while (running)
  {
    inputHandler.handleInput();
    renderer.update();
  }
  return 0;
}
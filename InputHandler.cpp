#include "InputHandler.h"

InputHandler::InputHandler(bool *_running, Renderer *_renderer)
{
  running = _running;
  // renderer = _renderer;
}

void InputHandler::handleInput()
{
  while (SDL_PollEvent(&event))
  {
    if (event.type == SDL_QUIT)
    {
      *running = false;
    }
  }
}
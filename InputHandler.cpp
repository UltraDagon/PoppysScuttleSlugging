#include "InputHandler.h"
#include <iostream>

InputHandler::InputHandler(bool *_running, Renderer *_renderer)
{
  running = _running;
  renderer = _renderer;
}

void InputHandler::handleInput()
{
  while (SDL_PollEvent(&event))
  {
    switch (event.type)
    {
    case SDL_QUIT:
      *running = false;
      break;
    case SDL_KEYDOWN:
      keysPressed[event.key.keysym.sym] = true;
      break;
    case SDL_KEYUP:
      keysPressed[event.key.keysym.sym] = false;
      break;
    default:
      break;
    }
  }

  // Adjust the camera according to input
  int rel_x = keysPressed[SDLK_RIGHT] - keysPressed[SDLK_LEFT];
  int rel_y = keysPressed[SDLK_DOWN] - keysPressed[SDLK_UP];
  double rel_zoom = 1 + 0.01 * keysPressed[SDLK_RIGHTBRACKET] - 0.01 * keysPressed[SDLK_LEFTBRACKET];

  renderer->adjustCamera(rel_x, rel_y, rel_zoom);
}
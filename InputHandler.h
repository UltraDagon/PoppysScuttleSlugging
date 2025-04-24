#include "Renderer.h"

#include <SDL2/SDL.h>
#include <unordered_map>

#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

class InputHandler
{
private:
  bool *running;
  Renderer *renderer;
  SDL_Event event;
  std::unordered_map<int, bool> keysPressed;

public:
  InputHandler(bool *_running, Renderer *_renderer); // Controls the running state of the program, the renderer,

  //~InputHandler();

  void handleInput();
};

#endif
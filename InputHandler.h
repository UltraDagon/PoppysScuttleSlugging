#include <SDL2/SDL.h>
#include "Renderer.h"

#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

class InputHandler
{
private:
  bool *running;
  Renderer *renderer;
  SDL_Event event;

public:
  InputHandler(bool *_running, Renderer *_renderer); // Controls the running state of the program, the renderer,

  //~InputHandler();

  void handleInput();
};

#endif
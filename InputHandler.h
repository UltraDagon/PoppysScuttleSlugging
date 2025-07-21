#include "Renderer.h"

#include <SDL2/SDL.h>
#include <unordered_map>

#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

class InputHandler
{
public: // TODO: Make private
  /// Pointer to the running variable that controls the gameloop.
  bool *running;
  /// Pointer to the Renderer that controls the window rendering and camera.
  Renderer *renderer;
  /// The event queue that contains all events that have occured after the previous frame.
  SDL_Event event;
  /// Map of all keyboard keys (true == pressed, false == unpressed).
  std::unordered_map<int, bool> keysPressed;
  /// X position of the mouse within the window.
  int mouseX;
  /// Y position of the mouse within the window.
  int mouseY;
  /// The state of the mouse buttons.
  Uint32 mouseState;

public:
  /**
   * Construct a new Input Handler object.
   * 
   * @param running_ the running variable that controls the gameloop
   * @param renderer_ the Renderer that controls the window rendering and camera
   */
  InputHandler(bool *_running, Renderer *_renderer);
  // Todo: flip underscores to the right ^, also maybe change these to references taken in at handleInput to save memory (not really needed)

  //~InputHandler();

  /**
   * Handle the input for the current frame and update InputHandler's variables.
   */
  void handleInput();
};

#endif
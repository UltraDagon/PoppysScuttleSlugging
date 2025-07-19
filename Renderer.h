#ifndef RENDERER_H
#define RENDERER_H

#include "Sprite.h"

#include <SDL2/SDL.h>
#include <vector>
#include <ctime>
#include <iostream> //DEBUG

class Camera
{
public: // Todo: Maybe make private
  int x;
  int y;
  double zoom;
  float transitionDuration;
  float transitionRemaining;
  std::pair<int, int> transitionOffset;

public:
  Camera();

  Camera(int _x, int _y, float _zoom);

  void transition(std::pair<int, int> offset, float duration);

  // TODO: replace transition with linear one by doing this:
  /*
  transition:
  take in:
    snapshot of current position relative to desired position (or just both positions), (can lowkey just be X)
    duration of transition

  save relative position, and whenever it focuses, add (1 - (timeElapsed/duration))*offset to the focused position
  possibly switch functions depending on whether or not there is a transition active or not, not sure how it will affect performance but I should test it!
  */
};

class Renderer
{
private:
  int windowWidth;
  int windowHeight;
  SDL_Window *window;
  SDL_Renderer *sdlRenderer;
  ImageCache *images;
  std::vector<Sprite *> sprites;
  Camera camera;

  clock_t initTime;
  clock_t prevFrameTime;
  clock_t currentFrameTime;

  void renderSprite(Sprite *sprite);

public:
  Renderer();

  Renderer(int _windowWidth, int _windowHeight);

  ~Renderer();

  /**
   * Get the Renderer's image cache.
   * @return ImageCache pointer
   */
  ImageCache *getImageCache();

  Camera &getCamera();

  /**
   * Get the deltaTime, or change in time between the most recently called Renderer::update() and the update before that.
   * @return The deltaTime (in seconds)
   */
  float deltaTime();

  /**
   * Get the width of the window.
   * @return the windows width (in pixels)
   */
  int getWindowWidth();

  /**
   * Get the width of the window.
   * @return the windows width (in pixels)
   */
  int getWindowHeight();

  /**
   * Get the Camera's current position.
   * @return The Camera's position as a pair (in pixels)
   */
  std::pair<int, int> getCameraPos();

  /**
   * Add a sprite to the vector of sprites to be rendered.
   * @param sprite Pointer to a sprite object
   */
  void addSprite(Sprite *sprite);

  /**
   * Deletes all sprites in the Renderer's vector of sprites.
   */
  void flushSprites();

  /**
   * Draws all sprites for the current frame.
   */
  void renderSprites();

  /**
   * Updates the window to display the current frame.
   */
  void update();

  /**
   * Moves the camera relative to it's current position.
   * @param rel_x The relative horizontal change (in pixels)
   * @param rel_y The relative vertical change (in pixels)
   * @param rel_zoom The relative zoom of the camera (multiplies with current zoom)
   */
  void adjustCamera(int rel_x, int rel_y, float rel_zoom = 1);

  // zoom into/out of point (x,y)
  // move to point (x,y)

  // Todo: If needed, change this to focusCamera(pos, type[left, center (default), right])
  void focusCameraLeft(std::pair<int, int> focusPoint);

  void transitionCamera(std::pair<int, int> offset, float duration);
};

#endif
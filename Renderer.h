#include "Sprite.h"

#include <SDL2/SDL.h>
#include <vector>
#include <ctime>
#include <iostream> //DEBUG

#ifndef RENDERER_H
#define RENDERER_H

class Camera
{
public: // Maybe make private
  int x;
  int y;
  double zoom;

public:
  Camera();
  Camera(int _x, int _y, double _zoom);
};

class Renderer
{
private:
  int windowWidth;
  int windowHeight;
  SDL_Window *window;
  SDL_Renderer *renderer;
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
   * Get the deltaTime, or change in time between the most recently called Renderer::update() and the update before that.
   * @return The deltaTime (in seconds).
   */
  float deltaTime();

  /**
   * Add a sprite to the vector of sprites to be rendered.
   * @param sprite Pointer to a sprite object.
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
   * @param rel_x The relative horizontal change (in pixels).
   * @param rel_y The relative vertical change (in pixels).
   * @param rel_zoom The relative zoom of the camera (multiplies with current zoom)
   */
  void adjustCamera(int rel_x, int rel_y, double rel_zoom = 1);

  // zoom into/out of point (x,y)
  // move to point (x,y)
};

#endif
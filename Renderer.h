#ifndef RENDERER_H
#define RENDERER_H

#include "Sprite.h"

#include <SDL2/SDL.h>
#include <vector>
#include <ctime>
#include <iostream> //DEBUG

/**
 * The Camera is used to translate the location of entities within the world to location on the window's screen.
 */
class Camera
{
public: // Todo: Maybe make private
  /// Horizontal position of the Camera in the world.
  int x;
  /// Vertical position of the Camera in the world.
  int y;
  /**
   * The zoom of the camera.
   *
   * When rendering, all sprites' size and distance from camera are multiplied by this amount.
   */
  double zoom;
  /// The total duration, in seconds, of the current Camera transition
  float transitionDuration;
  /// The remaining duration, in seconds, of the current Camera transition
  float transitionRemaining;
  /// The initial offset of the current Camera transition
  std::pair<int, int> transitionOffset;

public:
  /**
   * Camera constructor.
   *
   * @param x_ the initial x position of the Camera
   * @param y_ the initial y position of the Camera
   * @param zoom_ the initial zoom of the Camera
   */
  Camera(int x_ = 0, int y_ = 0, float zoom_ = 1);

  /**
   * Move the camera a relative distance over time.
   *
   * Ex: To pan the camera from (0,0) to (5,5) over 3 seconds, set the camera's position
   * to (5,5), then call transitionCamera({-5,-5}, 3).
   *
   * @param offset the offset relative to the camera's current position to move from
   * @param duration the time, in seconds, the transition should take before it stops moving
   */
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

/**
 * The Renderer is used to draw images onto the window that the user interacts with.
 */
class Renderer
{
private:
  /// The width of the window that the user interacts with.
  int windowWidth;
  /// The height of the window that the user interacts with.
  int windowHeight;
  /// Pointer to the SDL_Window.
  SDL_Window *window;
  /// Pointer to the SDL_Renderer.
  SDL_Renderer *sdlRenderer;
  /// The ImageCache that caches image files and SDL_Textures used by Sprites.
  ImageCache *images;
  /// The list of all Sprites to be rendered in the current frame.
  std::vector<Sprite *> sprites;
  /// The Camera used to translate the location of entities within the world to location on the window's screen.
  Camera camera;

  /// The time at which the game finished initializing
  clock_t initTime;
  /// The time at which the previous frame began
  clock_t prevFrameTime;
  /// The time at which the current frame began
  clock_t currentFrameTime;

  /**
   * Draw a Sprite onto the screen.
   *
   * @param sprite the sprite to be drawn
   */
  void renderSprite(Sprite *sprite);

public:
  /**
   * Renderer constructor.
   *
   * @param _windowWidth the width of the window that the user interacts with
   * @param _windowHeight the height of the window that the user interacts with
   */
  Renderer(int _windowWidth = 1600, int _windowHeight = 900);

  /// Renderer destructor.
  ~Renderer();

  /**
   * Get the Renderer's image cache.
   * @return pointer the Renderer's image cache
   */
  ImageCache *getImageCache();

  /**
   * Get a reference to the Camera used by the renderer.
   *
   * @return a reference to the Camera
   */
  Camera &getCamera();

  /**
   * Get the deltaTime, or change in time between the most recently called Renderer::update() and the update before that.
   * @return the deltaTime (in seconds)
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
   * @return the Camera's position as a pair (in pixels)
   */
  std::pair<int, int> getCameraPos();

  /**
   * Add a sprite to the vector of sprites to be rendered.
   * @param sprite Pointer to a sprite object
   */
  void addSprite(Sprite *sprite);

  /**
   * Add multiple sprites to the vector of sprites to be rendered.
   * @param sprites Vector of pointers to sprite objects
   */
  void addSprites(std::vector<Sprite *> sprites);

  // Todo: make template functions for entity children where you do addSprite(entity) (maybe addSpriteFrom, or change addSprite to addRawSprite) and it runs the current addSprite function to the getSprite of the object

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
  /**
   * Moves the camera to be focused onto a given location.
   *
   * @param focusPoint the position in the world to focus the gamera on
   */
  void focusCameraLeft(std::pair<int, int> focusPoint);

  /**
   * Move the camera a relative distance over time.
   *
   * Ex: To pan the camera from (0,0) to (5,5) over 3 seconds, set the camera's position
   * to (5,5), then call transitionCamera({-5,-5}, 3).
   *
   * @param offset the offset relative to the camera's current position to move from
   * @param duration the time, in seconds, the transition should take before it stops moving
   */
  void transitionCamera(std::pair<int, int> offset, float duration);
};

#endif
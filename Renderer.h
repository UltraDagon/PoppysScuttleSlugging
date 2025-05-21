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

  void addSprite(Sprite *sprite);

  void flushSprites();

  void renderSprites();

  void update();

  void adjustCamera(int rel_x, int rel_y, double rel_zoom = 1);

  // zoom into/out of point (x,y)
  // move to point (x,y)
};

#endif
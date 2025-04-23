#include "Sprite.h"

#include <SDL2/SDL.h>
#include <vector>
// #include <iostream> //DEBUG

#ifndef RENDERER_H
#define RENDERER_H

class Renderer
{
private:
  int width;
  int height;
  SDL_Window *window;
  SDL_Renderer *renderer;
  ImageCache *images;
  std::vector<Sprite *> sprites;

  void renderSprite(Sprite *sprite);

public:
  Renderer();

  Renderer(int _width, int _height);

  ~Renderer();

  void addSprite(Sprite *sprite);

  void flushSprites();

  void renderSprites();

  void update();
};

/*class Camera
{
public:
  Camera();
};*/

#endif
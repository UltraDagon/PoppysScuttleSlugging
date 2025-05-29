#include "ImageCache.h"

#include <SDL2/SDL.h>
#include <string>

#ifndef SPRITE_H
#define SPRITE_H

/**
 * A temporary object used by the Renderer to draw an image onto the screen.
 */
class Sprite
{
public: // make private
  int x;
  int y;
  int width;
  int height;

  SDL_Surface *surface;
  SDL_Texture *texture;

public:
  Sprite(int _x, int _y, int _width, int _height, std::string bmpAddress, ImageCache *images, SDL_Renderer *renderer);

  ~Sprite();

  SDL_Texture *getTexture();
};

#endif
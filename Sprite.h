#include "ImageCache.h"

#include <SDL2/SDL.h>
#include <string>

#ifndef SPRITE_H
#define SPRITE_H

/**
 * A temporary object used by the Renderer to draw an image onto the screen.
 * Sprites render using their positions as their centers.
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
  SDL_Rect frameRect; // Snippet of image to be rendered

public:
  Sprite(int _x, int _y, int _width, int _height, std::string bmpAddress, ImageCache *images);

  Sprite(int _x, int _y, int _width, int _height, std::pair<int, int> _frameSize, std::pair<int, int> _frameOffset, std::string bmpAddress, ImageCache *images);

  ~Sprite();

  SDL_Texture *getTexture(SDL_Renderer *sdlRenderer);
};

#endif
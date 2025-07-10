#include "Sprite.h"

// Phase out this constructor
Sprite::Sprite(int _x, int _y, int _width, int _height, std::string bmpAddress, ImageCache *images)
{
  x = _x;
  y = _y;

  width = _width;
  height = _height;
  surface = images->get_image(bmpAddress);
  SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 254, 1, 254));

  frameRect = {0, 0, _width, _height};
}

// Todo: look up if _ should be on other side
Sprite::Sprite(int _x, int _y, int _width, int _height, std::pair<int, int> frameSize, std::pair<int, int> frameOffset, std::string bmpAddress, ImageCache *images)
{
  x = _x;
  y = _y;

  width = _width;
  height = _height;
  surface = images->get_image(bmpAddress);

  frameRect = {frameOffset.first, frameOffset.second, frameSize.first, frameSize.second};
}

Sprite::~Sprite()
{
  SDL_DestroyTexture(texture);
}

SDL_Texture *Sprite::getTexture(SDL_Renderer *sdlRenderer)
{
  texture = SDL_CreateTextureFromSurface(sdlRenderer, surface);
  return texture;
}
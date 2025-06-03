#include "Sprite.h"

Sprite::Sprite(int _x, int _y, int _width, int _height, std::string bmpAddress, ImageCache *images)
{
  x = _x;
  y = _y;
  width = _width;
  height = _height;
  surface = images->get_image(bmpAddress);
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
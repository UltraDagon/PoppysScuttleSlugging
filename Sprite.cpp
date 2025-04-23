#include "Sprite.h"

Sprite::Sprite(int _x, int _y, int _width, int _height, std::string bmpAddress, ImageCache *images, SDL_Renderer *renderer)
{
  x = _x;
  y = _y;
  width = _width;
  height = _height;
  surface = images->get_image(bmpAddress);
  texture = SDL_CreateTextureFromSurface(renderer, surface);
}

Sprite::~Sprite()
{
  SDL_DestroyTexture(texture);
}

SDL_Texture *Sprite::getTexture()
{
  return texture;
}
#include "Sprite.h"

// Phase out this constructor
Sprite::Sprite(int _x, int _y, int _width, int _height, std::string bmpAddress_, ImageCache *images)
{
  x = _x;
  y = _y;

  width = _width;
  height = _height;
  bmpAddress = bmpAddress_;
  // surface = images->get_image(bmpAddress);
  // SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 254, 1, 254));

  frameRect = {0, 0, _width, _height};
}

Sprite::Sprite(int x_, int y_, int width_, int height_, std::pair<int, int> frameSize, std::pair<int, int> frameOffset, std::string bmpAddress_, ImageCache *images)
{
  x = x_;
  y = y_;

  width = width_;
  height = height_;
  bmpAddress = bmpAddress_;
  // surface = images->get_image(bmpAddress);

  frameRect = {frameOffset.first, frameOffset.second, frameSize.first, frameSize.second};
}

Sprite::~Sprite()
{
  texture = nullptr;
}

SDL_Texture *Sprite::getTexture(SDL_Renderer *sdlRenderer, ImageCache *images)
{
  // texture = SDL_CreateTextureFromSurface(sdlRenderer, surface);
  return images->getTexture(bmpAddress, sdlRenderer);
}
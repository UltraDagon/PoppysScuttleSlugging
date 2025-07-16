#include <SDL2/SDL.h>
#include <map>
#include <string>

#include <iostream>

#ifndef IMAGECACHE_H
#define IMAGECACHE_H

class ImageCache
{
private:
  std::map<std::string, SDL_Surface *> surfaceCache;
  std::map<std::string, SDL_Texture *> textureCache;

public:
  SDL_Surface *getSurface(std::string file);

  SDL_Texture *getTexture(std::string file, SDL_Renderer *sdlRenderer);

  void flush();

  ~ImageCache();
};

#endif
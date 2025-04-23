#include <SDL2/SDL.h>
#include <map>
#include <string>

#ifndef IMAGECACHE_H
#define IMAGECACHE_H

class ImageCache
{
private:
  std::map<std::string, SDL_Surface *> cache;

public:
  SDL_Surface *get_image(std::string file);

  void flush();

  ~ImageCache();
};

#endif
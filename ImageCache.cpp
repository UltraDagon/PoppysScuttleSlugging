#include "ImageCache.h"

// Filename is input
SDL_Surface *ImageCache::get_image(std::string file)
{
  auto i = cache.find(file);
  if (i == cache.end())
  {
    SDL_Surface *surf = SDL_LoadBMP(file.c_str());
    i = cache.insert(i, make_pair(file, surf));
  }
  return i->second;
}

void ImageCache::flush()
{
  std::map<std::string, SDL_Surface *>::iterator i = cache.begin();
  for (; i != cache.end(); ++i)
  {
    SDL_FreeSurface(i->second);
  }
  cache.clear();
}

ImageCache::~ImageCache()
{
  flush();
}
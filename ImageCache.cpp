#include "ImageCache.h"

// Filename is input
SDL_Surface *ImageCache::getSurface(std::string file)
{
  auto i = surfaceCache.find(file);
  if (i == surfaceCache.end())
  {
    SDL_Surface *surf = SDL_LoadBMP(file.c_str());
    i = surfaceCache.insert(i, make_pair(file, surf));
  }
  return i->second;
}

SDL_Texture *ImageCache::getTexture(std::string file, SDL_Renderer *sdlRenderer)
{
  auto i = textureCache.find(file);
  if (i == textureCache.end())
  {
    SDL_Texture *texture = SDL_CreateTextureFromSurface(sdlRenderer, getSurface(file));
    i = textureCache.insert(i, make_pair(file, texture));
  }
  return i->second;
}

void ImageCache::flush()
{
  std::map<std::string, SDL_Surface *>::iterator i = surfaceCache.begin();
  for (; i != surfaceCache.end(); ++i)
  {
    SDL_FreeSurface(i->second);
  }
  surfaceCache.clear();

  std::map<std::string, SDL_Texture *>::iterator j = textureCache.begin();
  for (; j != textureCache.end(); ++i)
  {
    SDL_DestroyTexture(j->second);
  }
  textureCache.clear();
}

ImageCache::~ImageCache()
{
  flush();
}
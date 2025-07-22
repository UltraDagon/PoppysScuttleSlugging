#include <SDL2/SDL.h>
#include <map>
#include <string>

#include <iostream>

#ifndef IMAGECACHE_H
#define IMAGECACHE_H

/**
 * Manager for using images to be displayed in the program.
 * 
 * By default the image cache only accesses images in the "assets/" folder.
 */
class ImageCache
{
private:
  /// Cache for storing the SDL_Surface* for a given image file.
  std::map<std::string, SDL_Surface *> surfaceCache;
  /// Cache for storing the SDL_Texture* for a given image file.
  std::map<std::string, SDL_Texture *> textureCache;

public:
  /**
   * Get and cache an SDL_Surface object.
   * 
   * @param file the name of the image file in the assets folder
   * @return pointer to the cached SDL_Surface
   */
  SDL_Surface *getSurface(std::string file);

  /**
   * Get and cache an SDL_Texture object.
   * 
   * @param file the name of the image file in the assets folder
   * @param sdlRenderer the SDL_Renderer that will display the texture
   * @return pointer to the cached SDL_Texture
   */
  SDL_Texture *getTexture(std::string file, SDL_Renderer *sdlRenderer);

  /**
   * Clear out the surface and texture caches.
   */
  void flush();

  ~ImageCache();
};

#endif
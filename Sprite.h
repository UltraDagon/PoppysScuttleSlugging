#include "ImageCache.h"

#include <SDL2/SDL.h> // Todo: maybe this can be removed? I think imagecache has sdl2/sdl.h
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
  /// The name of the image file that will be rendered from.
  std::string bmpAddress;
  /// The pointer of the texture used to render the Sprite.
  SDL_Texture *texture;
  /// The rect within the image to render to the screen. Must be smaller than the image dimensions.
  SDL_Rect frameRect;

public:
// Phase this one out
  Sprite(int _x, int _y, int _width, int _height, std::string bmpAddress, ImageCache *images);

  /**
   * Construct a new Sprite object.
   * 
   * @param x_ x position in the world
   * @param y_ y position in the world
   * @param width_ width of the sprite in the world
   * @param height_ height of the sprite in the world
   * @param frameSize size of the frame within the image file
   * @param frameOffset offset of the frame from the top left of the image file
   * @param bmpAddress_ name of the image file
   * @param images the ImageCache that manages image files
   */
  Sprite(int x_, int y_, int width_, int height_, std::pair<int, int> frameSize, std::pair<int, int> frameOffset, std::string bmpAddress_, ImageCache *images);

  /**
   * Destroy the Sprite object.
   */
  ~Sprite();

  /**
   * Get the SDL_Texture of the Sprite.
   * 
   * @param sdlRenderer the SDL_Renderer that the Sprite will be renderered on
   * @param images the ImageCache that manages image files
   * @return pointer to the SDL_Texture of the Sprite
   */
  SDL_Texture *getTexture(SDL_Renderer *sdlRenderer, ImageCache *images);
};

#endif
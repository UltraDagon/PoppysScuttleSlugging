#include <SDL2/SDL.h>
#include <vector>
#include <map>    // ImageCache
#include <string> // ImageCache
// #include <iostream> //DEBUG

#ifndef RENDERER_H
#define RENDERER_H

class ImageCache // ImageCache
{
private:
  std::map<std::string, SDL_Surface *> cache;

public:
  SDL_Surface *get_image(std::string file);

  void flush();

  ~ImageCache();
};

class Sprite
{
private:
  int x;
  int y;
  int width;
  int height;

  SDL_Surface *surface;
  SDL_Texture *texture;

public:
  Sprite(int _x, int _y, int _width, int _height, std::string bmpAddress, ImageCache *images, SDL_Renderer *renderer);

  ~Sprite();

  SDL_Texture *getTexture();
};

class Renderer
{
private:
  int width;
  int height;
  SDL_Window *window;
  SDL_Renderer *renderer;
  ImageCache *images;
  std::vector<Sprite *> sprites;

  void renderSprite(Sprite *sprite);

public:
  Renderer();

  Renderer(int _width, int _height);

  ~Renderer();

  void addSprite(Sprite *sprite);

  void flushSprites();

  void renderSprites();

  void update();
};

/*class Camera
{
public:
  Camera();
};*/

#endif
#include <SDL2/SDL.h>

#ifndef RENDERER_H
#define RENDERER_H

class Renderer
{
private:
  int width;
  int height;
  SDL_Window *window;
  SDL_Renderer *renderer;

public:
  Renderer();

  Renderer(int _width, int _height);

  Renderer(int _width, int _height, SDL_Window &_window, SDL_Renderer &_renderer);

  ~Renderer();

  void update();
};

/*class Camera
{
public:
  Camera();
};*/

#endif
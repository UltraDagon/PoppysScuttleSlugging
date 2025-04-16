#include "Renderer.h"

Renderer::Renderer()
{
  SDL_Init(SDL_INIT_EVERYTHING);

  width = 0;
  height = 0;
  window = SDL_CreateWindow("Hello SDL World", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_ALLOW_HIGHDPI);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

Renderer::Renderer(int _width, int _height)
{
  SDL_Init(SDL_INIT_EVERYTHING);

  width = _width;
  height = _height;
  window = SDL_CreateWindow("Hello SDL World", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
  renderer = SDL_CreateRenderer(window, -1, 0);
}

Renderer::~Renderer()
{
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
}

void Renderer::update()
{
  SDL_SetRenderDrawColor(renderer, 191, 191, 255, 255);
  SDL_RenderClear(renderer);
  SDL_RenderPresent(renderer);
}
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
  images = new ImageCache();
}

Renderer::~Renderer()
{
  delete images;
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
}

void Renderer::addSprite(Sprite *sprite)
{
  sprites.push_back(sprite);
}

void Renderer::flushSprites()
{
  while (sprites.size() > 0)
  {
    delete sprites.at(0);
    sprites.erase(sprites.begin());
  }
}

void Renderer::renderSprite(Sprite *sprite)
{
  SDL_Rect destination;
  destination.x = 200;
  destination.y = 200;
  destination.w = 100;
  destination.h = 100;

  SDL_RenderCopy(renderer, sprite->getTexture(), NULL, &destination);
}

void Renderer::renderSprites()
{
  for (Sprite *s : sprites)
  {
    renderSprite(s);
  }
}

void Renderer::update()
{
  SDL_SetRenderDrawColor(renderer, 191, 191, 255, 255);
  SDL_RenderClear(renderer);

  addSprite(new Sprite(200, 200, 100, 100, "assets/image.bmp", images, renderer));
  renderSprites();
  flushSprites(); // After rendering, free up space for the next frame of sprites

  SDL_RenderPresent(renderer);
}
#include "Renderer.h"

Camera::Camera()
{
  x = 0;
  y = 0;
  zoom = 1;
}

Camera::Camera(int _x, int _y, double _zoom)
{
  x = _x;
  y = _y;
  zoom = _zoom;
}

Renderer::Renderer()
{
  SDL_Init(SDL_INIT_EVERYTHING);

  windowWidth = 0;
  windowHeight = 0;
  window = SDL_CreateWindow("Hello SDL World", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_ALLOW_HIGHDPI);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

Renderer::Renderer(int _windowWidth, int _windowHeight)
{
  SDL_Init(SDL_INIT_EVERYTHING);

  windowWidth = _windowWidth;
  windowHeight = _windowHeight;
  window = SDL_CreateWindow("Hello SDL World", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
  renderer = SDL_CreateRenderer(window, -1, 0);
  images = new ImageCache();
  camera = Camera(0, 0, 1);
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

  destination.w = sprite->width * camera.zoom;
  destination.h = sprite->height * camera.zoom;
  // Maybe need to change windowWidth and windowHeight to a "focus" variable for where the camera zooms into/out of
  destination.x = windowWidth / 2 + (sprite->x - camera.x) * camera.zoom - destination.w * 0.5; // Center the sprites at their origin
  destination.y = windowHeight / 2 + (sprite->y - camera.y) * camera.zoom - destination.h * 0.5;

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
  addSprite(new Sprite(250, 350, 100, 100, "assets/image.bmp", images, renderer));
  addSprite(new Sprite(400, 300, 100, 100, "assets/image.bmp", images, renderer));
  renderSprites();
  flushSprites(); // After rendering, free up space for the next frame of sprites

  SDL_RenderPresent(renderer);
}

void Renderer::adjustCamera(int rel_x, int rel_y, double rel_zoom)
{
  camera.x += rel_x;
  camera.y += rel_y;
  camera.zoom *= rel_zoom;
}
#include "Renderer.h"

Camera::Camera()
{
  x = 0;
  y = 0;
  zoom = 1;
  transitionDuration = 1;
  transitionRemaining = 0;
  transitionOffset = {0, 0};
}

Camera::Camera(int _x, int _y, float _zoom)
{
  x = _x;
  y = _y;
  zoom = _zoom;
  transitionDuration = 1;
  transitionRemaining = 0;
  transitionOffset = {0, 0};
}

void Camera::transition(std::pair<int, int> offset, float duration)
{
  transitionRemaining = duration;
  transitionOffset = offset;

  if (duration <= 0) // Don't divide by zero silly!
    duration = 1;
  transitionDuration = duration;
}

Renderer::Renderer()
{
  SDL_Init(SDL_INIT_EVERYTHING);

  windowWidth = 0;
  windowHeight = 0;
  window = SDL_CreateWindow("Hello SDL World", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_ALLOW_HIGHDPI);
  sdlRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

Renderer::Renderer(int _windowWidth, int _windowHeight)
{
  SDL_Init(SDL_INIT_EVERYTHING);

  windowWidth = _windowWidth;
  windowHeight = _windowHeight;
  window = SDL_CreateWindow("Poppy's Scuttle Slugging!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
  sdlRenderer = SDL_CreateRenderer(window, -1, 0);
  images = new ImageCache();
  camera = Camera(0, 0, 1);

  initTime = prevFrameTime = currentFrameTime = clock();
  std::cout << "initTime: " << initTime << ", prevFrameTime: " << prevFrameTime << ", currentFrameTime: " << currentFrameTime << std::endl;
}

Renderer::~Renderer()
{
  delete images;
  SDL_DestroyRenderer(sdlRenderer);
  SDL_Quit();
}

ImageCache *Renderer::getImageCache()
{
  return images;
}

Camera &Renderer::getCamera()
{
  return camera;
}

float Renderer::deltaTime()
{
  // FPS (Frames Per Second) = 1.0f / deltaTime()
  return ((float)currentFrameTime - float(prevFrameTime)) / CLOCKS_PER_SEC;
}

int Renderer::getWindowWidth()
{
  return windowWidth;
}

std::pair<int, int> Renderer::getCameraPos()
{
  return std::pair<int, int>{camera.x, camera.y};
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

  SDL_RenderCopy(sdlRenderer, sprite->getTexture(sdlRenderer), &sprite->frameRect, &destination); //&sprite->frameRect
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
  SDL_SetRenderDrawColor(sdlRenderer, 191, 191, 255, 255);
  SDL_RenderClear(sdlRenderer);
  renderSprites();
  flushSprites(); // After rendering, free up space for the next frame of sprites

  SDL_RenderPresent(sdlRenderer);

  prevFrameTime = currentFrameTime; // Save last frame time
  currentFrameTime = clock();       // Get current frame time, difference is time the last frame took to process/render

  std::cout << 1.0f / deltaTime() << "fps" << std::endl;
}

void Renderer::adjustCamera(int rel_x, int rel_y, float rel_zoom)
{
  camera.x += rel_x;
  camera.y += rel_y;
  camera.zoom *= rel_zoom;

  if (camera.zoom < 0)
    camera.zoom = 1;
}

// Maybe make this a camera function?
void Renderer::focusCameraLeft(std::pair<int, int> position)
{
  camera.x = position.first + windowWidth / 6; // Object is 1/3 of the window width from the left

  if (position.second < -350)
    camera.y = position.second + 350;
  else
    camera.y = 0;

  if (camera.transitionRemaining > 0) // If there is a transition active
  {
    camera.x += camera.transitionOffset.first * (camera.transitionRemaining / camera.transitionDuration);
    camera.y += camera.transitionOffset.second * (camera.transitionRemaining / camera.transitionDuration);
    camera.transitionRemaining -= deltaTime();
  }
}

void Renderer::transitionCamera(std::pair<int, int> offset, float duration)
{
  camera.transition(offset, duration);
}
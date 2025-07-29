#include "Environment.h"

Environment::Environment()
{
  parallax = 0;
}

/**
 * TODO: Finish parralax
 * Note that for environments, position.first is the offset of the image used rather than the starting x position, as the image should repeat along the x axis infinitely
 */
Environment::Environment(std::pair<float, float> position_, std::pair<int, int> size_, float parallax_)
{
  position = position_;
  size = size_;
  parallax = parallax_;
}

std::vector<Sprite *> Environment::getSprites(Renderer &renderer)
{
  std::vector<Sprite *> output;
  // These work by finding the amount of widths needed to reach the left side and right side of the screen from the center (screenWidth/2), then rounding up, then multiplying by the size of the widths, then removing the offset caused by the entity's position being their center
  int startPos = -1 * ceil((0.5 * renderer.getWindowWidth() - renderer.getCameraPos().first) / size.first) * size.first + size.first / 2;
  int endPos = ceil((0.5 * renderer.getWindowWidth() + renderer.getCameraPos().first) / size.first) * size.first + size.first / 2;

  for (int xPos = startPos; xPos < endPos; xPos += size.first)
  {
    output.push_back(new Sprite((int)position.first % size.first + xPos, position.second, size.first, size.second, animationData.frameSize, {0, 0}, "assets/image.bmp", renderer.getImageCache()));
  }

  return output;
}
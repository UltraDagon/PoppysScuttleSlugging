#include "Environment.h"

Environment::Environment()
{
  parallax = 0;
}

/**`
 * TODO: Finish parralax
 * Note that for environments, position.first is the offset of the image used rather than the starting x position, as the image should repeat along the x axis infinitely
 */
Environment::Environment(std::string spriteSheet_, std::pair<float, float> position_, std::pair<int, int> size_, float parallax_)
{
  spriteSheet = spriteSheet_;
  position = position_;
  size = size_;
  parallax = parallax_;
}

std::vector<Sprite *> Environment::getSprites(Renderer &renderer)
{
  std::vector<Sprite *> output;
  const int camX = renderer.getCameraPos().first;

  // https://www.desmos.com/calculator/rws8fujqig
  // Small note, the reason Poppy and the Scuttle have a startingX variable is because the rendering messes up if camX is too low.
  int startPos = -1 * (renderer.getWindowWidth() - camX + (int)(position.first + camX * parallax) % size.first - (int)(renderer.getWindowWidth() / 2 + position.first + camX * parallax - camX) % size.first) + renderer.getWindowWidth() / 2 + size.first / 2;
  int endPos = startPos + ceil(renderer.getWindowWidth() / size.first + 1) * size.first;

  for (int xPos = startPos; xPos < endPos; xPos += size.first)
  {
    output.push_back(new Sprite((int)(position.first + renderer.getCameraPos().first * parallax) % size.first + xPos, position.second + renderer.getCameraPos().second * parallax, size.first, size.second, animationData.frameSize, {0, 0}, "assets/" + spriteSheet, renderer.getImageCache()));
  }

  return output;
}
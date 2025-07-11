#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "Entity.h"

/**
 * Environment objects are entities used to render the environment.
 */
class Environment : public Entity
{
private:
  /**
   * Parralax is the rate at which the sprite moves relative to the camera. (0 to 1)
   * 0: The object is close to the camera. When the camera moves, the object moves on the screen.
   * 1: The object is far from the camera. When the camera moves, the object remains still on the screen.
   */
  float parallax; // Todo: implement

public:
  Environment();

  Environment(std::pair<float, float> position_, std::pair<int, int> size_, float parallax_);

  /**
   * @return All sprites needed to render an environment texture that is repeating on the x-axis
   */
  std::vector<Sprite *> getSprites(ImageCache *images, Renderer &renderer);
};

#endif
#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "Entity.h"

/**
 * Environment objects are entities used to render the environment.
 *
 * Ex: the floor and background.
 */
class Environment : public Entity
{
private:
  /**
   * The rate at which the sprite moves relative to the camera. (0 to 1)
   * 0: The object is close to the camera. When the camera moves, the object moves on the screen.
   * 1: The object is far from the camera. When the camera moves, the object remains still on the screen.
   */
  float parallax; // Todo: implement

public:
  /// Environment object constructor.
  Environment();

  /**
   * Environment object constructor.
   *
   * @param position_ first: the x offset of the x-axis repeating entity, second: the y position of the entity in the world
   * @param size_ the size of the entity.
   * @param parallax_ the rate at which the sprite moves relative to the camera. (0 to 1)
   */
  Environment(std::pair<float, float> position_, std::pair<int, int> size_, float parallax_);

  /**
   * Get all sprites needed to render an Environment's texture that is repeating on the x-axis.
   *
   * @param images the ImageCache that manages image files
   * @param renderer the Renderer that controls the window rendering and camera
   * @return the vector of Sprites needed to render the Environment entity
   */
  std::vector<Sprite *> getSprites(ImageCache *images, Renderer &renderer);
};

#endif
#ifndef ENTITY_H
#define ENTITY_H

#include "../Sprite.h"
#include "../Renderer.h"

#include <utility>
#include <memory>
#include <cmath>
#include <unordered_map>
#include <random>

/// The position of the floor hitbox that the Scuttle Crab bounces on and monsters walk on
const int WORLD_FLOOR_Y = 350;
/// Constant downwards velocity applied to the Scuttle Crab in pixels per second^2
const int WORLD_GRAVITY = 100;

/**
 * Object that stores the position and animation data of an Entity in the world.
 *
 * Children of this parent contain data more specific to the type of entity of the child.
 */
class Entity
{
public:
  /// The Entity's position in the world.
  std::pair<float, float> position;
  /// The Entity's hitbox and sprite size.
  std::pair<int, int> size;
  /// The name of the image file used to render the Entity.
  std::string spriteSheet;
  /// All data related to animating sprites.
  struct
  {
    /// The size of the frame rectangle within the sprite sheet. If either are negative, the entire texture is rendered.
    std::pair<int, int> frameSize = {-1, -1};
    /// The total animation frames (columns) in the sprite sheet
    int totalFrames = 1;
    /// Which animation (row of frames) is playing. If negative, don't render the Entity.
    float animation = 0;
    /// How many frames per second the animation plays at.
    float speed = 1;
    /// The current frame (column) that the animation is on
    float currentFrame = 0;
  } animationData;

  /// Entity object constructor.
  Entity();

  /**
   * Get the Sprite object used to render the Entity.
   *
   * @param images the ImageCache that manages image files
   * @return pointer to the newly constructed Sprite object
   */
  virtual Sprite *getSprite(ImageCache *images);

  /**
   * Adds the sprite of the Entity to the renderer's vector of sprites to render.
   *
   * @param renderer the Renderer that controls the window rendering and camera
   */
  virtual inline void render(Renderer &renderer)
  {
    renderer.addSprite(getSprite(renderer.getImageCache()));
  };

  /**
   * Progress/loop the animation of the Entity.
   *
   * @param deltaTime the time that has elapsed since the previous frame
   */
  void updateAnimation(float &deltaTime);
};

#endif // ENTITY_H

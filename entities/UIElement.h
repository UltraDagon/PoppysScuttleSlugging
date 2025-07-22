#ifndef UIELEMENT_H
#define UIELEMENT_H

#include "Entity.h"

/**
 * UI Elements are Entities that are able to be positioned relative to a parent.
 */
class UIElement : public Entity
{
public:
  /// Determines whether the UIElement is rendered or not.
  bool active = true;
  /**
   * The UIElement's position is relative to this parent UIElement.
   * 
   * If nullptr, the position is relative to the world.
   */
  UIElement *parent = nullptr;

  /**
   * Get the absolute position in the world of the UIElement.
   * 
   * @return the position relative to the world
   */
  std::pair<int, int> absolutePosition();

public:
  UIElement();

  UIElement(std::pair<int, int> position_, std::pair<int, int> size_, std::string spriteSheet_, UIElement *parent_ = nullptr);

  Sprite *getSprite(ImageCache *images);
};

#endif
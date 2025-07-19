#ifndef UIELEMENT_H
#define UIELEMENT_H

#include "Entity.h"

/**
 * UI Elements are Entities that are able to be positioned relative to a parent
 * Entity and are able to be clickable buttons.
 */
class UIElement : public Entity
{
public:
  bool active = true;
  UIElement *parent = nullptr;

  std::pair<int, int> absolutePosition();

public:
  UIElement();

  UIElement(std::pair<int, int> position_, std::pair<int, int> size_, std::string spriteSheet_, UIElement *parent_ = nullptr);

  Sprite *getSprite(ImageCache *images);
};

#endif
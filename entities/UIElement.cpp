#include "UIElement.h"

UIElement::UIElement()
{
}

UIElement::UIElement(std::pair<int, int> position_, std::pair<int, int> size_, std::string spriteSheet_, UIElement *parent_)
{
  position = position_;
  size = size_;
  spriteSheet = spriteSheet_;
  // Todo: maybe make some sort of loop prevention?
  parent = parent_;
}

Sprite *UIElement::getSprite(ImageCache *images)
{
  int finalXPosition = position.first;
  int finalYPosition = position.second;
  UIElement *currentParent = parent;

  while (currentParent != nullptr)
  {
    finalXPosition += currentParent->position.first;
    finalYPosition += currentParent->position.second;
    currentParent = currentParent->parent;
  }

  return new Sprite(finalXPosition, finalYPosition, size.first, size.second, animationData.frameSize, {floor(animationData.currentFrame) * animationData.frameSize.first, animationData.animation * animationData.frameSize.first}, "assets/" + spriteSheet, images);
}
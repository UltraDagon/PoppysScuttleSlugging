#include "UIElement.h"

char UIElement::ButtonData::getNewState(int &mouseX, int &mouseY, bool &leftClickDown)
{
  // If mouse pos isn't inside of the button
  if (mouseX < x - w / 2 || x + w / 2 < mouseX ||
      mouseY < y - h / 2 || y + h / 2 < mouseY)
    return 'd'; // Button is in default state

  if (leftClickDown)
    return 'p'; // Button is pressed

  // If button was pressed last frame but left click no longer held down
  if (state == 'p')
    return 'c'; // Button has been clicked

  return 'h'; // Button is hovered
}

std::pair<int, int> UIElement::absolutePosition()
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

  return {finalXPosition, finalYPosition};
}

UIElement::UIElement()
{
}

UIElement::UIElement(std::pair<int, int> position_, std::pair<int, int> size_, std::string spriteSheet_, UIElement *parent_)
{
  position = position_;
  size = size_;
  spriteSheet = spriteSheet_;
  parent = parent_;
}

Sprite *UIElement::getSprite(ImageCache *images)
{
  std::pair<int, int> absPos = absolutePosition();

  return new Sprite(absPos.first, absPos.second, size.first, size.second, animationData.frameSize, {floor(animationData.currentFrame) * animationData.frameSize.first, animationData.animation * animationData.frameSize.second}, "assets/" + spriteSheet, images);
}
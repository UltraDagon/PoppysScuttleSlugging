#include "Entity.h"

Entity::Entity()
{
  position = {0.0f, 0.0f};
  size = {100, 100};
  spriteSheet = "image.bmp";
  animationData.frameSize = {1215, 717};
}

Entity::Entity(std::pair<float, float> position_, std::pair<int, int> size_)
{
  position = position_;
  size = size_;
}

Sprite *Entity::getSprite(ImageCache *images)
{
  return new Sprite(position.first, position.second, size.first, size.second, animationData.frameSize, {floor(animationData.currentFrame) * animationData.frameSize.first, animationData.animation * animationData.frameSize.first}, "assets/" + spriteSheet, images);
}

void Entity::updateAnimation(float &deltaTime)
{
  animationData.currentFrame += animationData.speed * deltaTime;
  if (animationData.currentFrame > animationData.totalFrames)
    animationData.currentFrame -= animationData.totalFrames;
}
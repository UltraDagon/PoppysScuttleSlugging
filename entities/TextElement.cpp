#include "TextElement.h"

TextElement::TextElement(std::string text_, std::pair<int, int> position_, std::pair<int, int> size_, unsigned int widthThinning, UIElement *parent_)
    : text(text_)
{
  position = position_;
  size = size_;
  parent = parent_;
  animationData.frameSize = {DEFAULT_FONT_SIZE - widthThinning, DEFAULT_FONT_SIZE};
}

TextElement::TextElement(std::string text_, std::pair<int, int> position_, int charSize, TextAlignment align, unsigned int widthThinning, UIElement *parent_)
    : text(text_)
{
  position = position_;
  size = {text.size() * (charSize - widthThinning), charSize};
  parent = parent_;
  animationData.frameSize = {DEFAULT_FONT_SIZE - widthThinning, DEFAULT_FONT_SIZE};

  switch (align)
  {
  case TextAlignment::LEFT:
    position.first -= size.first / 2;
    break;
  case TextAlignment::RIGHT:
    position.first += size.first / 2;
    break;
  }
}

std::vector<Sprite *> TextElement::getSprites(Renderer &renderer)
{
  std::vector<Sprite *> sprites;
  // Position of character on the font spritesheet, if char is not found: its a space
  for (int i = 0; i < text.size(); ++i)
  {
    if (65 <= text[i] && text[i] <= 90) // Capital letter
      animationData.animation = text[i] - 65;

    else if (97 <= text[i] && text[i] <= 122) // Lowercase letter
      animationData.animation = text[i] - 97;

    else if (48 <= text[i] && text[i] <= 57) // Number
      animationData.animation = text[i] - 48 + 26;

    else if (text[i] == 39) // Single quote (')
      animationData.animation = 36;

    else
      animationData.animation = -1;

    sprites.push_back(new Sprite(i * size.first / text.size() + position.first - size.first / 2, position.second, size.first / text.size(), size.second, animationData.frameSize, {(animationData.frameSize.second - animationData.frameSize.first) / 2, animationData.animation * animationData.frameSize.second}, "assets/default_font.bmp", renderer.getImageCache()));
  }

  return sprites;
}

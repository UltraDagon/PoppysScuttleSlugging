#ifndef TEXTELEMENT_H
#define TEXTELEMENT_H

#include "UIElement.h"

class TextElement : public UIElement
{
public:
  enum class TextAlignment
  {
    LEFT,
    CENTER,
    RIGHT
  };

private:
  /// The width and height of the characters in default_font.bmp
  const int DEFAULT_FONT_SIZE = 64;

  /// The text to be displayed. Valid characters: A-Z 0-9 '
  std::string text;
  /// The alignment of the text to branch out from.
  TextAlignment align;

public:
  /**
   * Construct a TextElement that renders within a rect given by the position and size, as other entities do.
   *
   * @param text_ the text to render
   * @param position_ the position of the TextElement's center
   * @param size_ the size of the TextElement
   * @param widthThinning cut off this many pixels from the width of each char
   * @param parent_ the parent element of the text, whos position is the reference for this element's position
   */
  TextElement(std::string text_, std::pair<int, int> position_, std::pair<int, int> size_, unsigned int widthThinning = 0, UIElement *parent_ = nullptr);

  /**
   * Construct a TextElement that renders from a starting point and braches in direction.
   *
   * @param text_ the text to render
   * @param position_ the position of the first character's center
   * @param charSize the size (in pixels) of the characters
   * @param align_ the alignment of the text to branch out from
   * @param widthThinning cut off this many pixels from the width of each char
   * @param parent_ the parent element of the text, whos position is the reference for this element's position
   */
  TextElement(std::string text_, std::pair<int, int> position_, int charSize, TextAlignment align_, unsigned int widthThinning = 0, UIElement *parent_ = nullptr);

  /**
   * Get all sprites needed to render the text.
   *
   * @param renderer the Renderer that controls the window rendering and camera
   * @return the vector of Sprites needed to render the text
   */
  std::vector<Sprite *> getSprites(Renderer &renderer);
};

#endif // TEXTELEMENT_H
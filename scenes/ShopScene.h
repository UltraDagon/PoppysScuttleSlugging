#ifndef SHOPSCENE_H
#define SHOPSCENE_H

#include "../entities/UIElement.h"
// #include "../entities/Entity.h"

#include "../Renderer.h"
#include "../ResourceManager.h"
#include "../ImageCache.h"
#include "../InputHandler.h"

struct ButtonData
{
  int x;
  int y;
  int w;
  int h;
  char state = 'd'; // d: default, h: hovered, p: pressed
};

class ShopScene
{
public:
  ResourceManager *resourceManager;
  std::unordered_map<std::string, ButtonData> buttons; // Buttons have a name (key) and rect [x,y,w,h] (value)

  /**
   * Render the UIElements to display an upgrade in the shop.
   *
   * @param index the positon of the upgrade on the shop board. (0 <= index < 6)
   * @param resource the name of the resource in saveData that will be upgraded and displayed.
   * @param name_ the name of the upgrade that will be displayed.
   * @param icon_ the name of the image file to be used as the upgrade's icon.
   * @param renderer the renderer object used to draw to the window.
   * @param parent the parent object (should be an upgrade board) that the upgrade will render inside of.
   */
  void renderUpgrade(int index, std::string resource, std::string name_, std::string icon_, Renderer &renderer, UIElement *parent = nullptr);

public:
  ShopScene();

  /**
   * Render the shop scene.
   *
   * @param renderer the renderer object used to draw to the window.
   */
  void render(Renderer &renderer);

  void physicsStep(float deltaTime, InputHandler &input, Renderer &renderer); // todo: maybe rename?

  /**
   * Set the ResourceManager to be read from and written to by the shop scene.
   *
   * @param resManager the resource manager to be used.
   */
  void setResourceManager(ResourceManager &resManager);
};

#endif
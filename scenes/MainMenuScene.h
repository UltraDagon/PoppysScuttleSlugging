#ifndef MAINMENUSCENE_H
#define MAINMENUSCENE_H

#include "../entities/TextElement.h"

#include "../Renderer.h"
#include "../ResourceManager.h"
#include "../InputHandler.h"
#include "../ImageCache.h"

class MainMenuScene
{
public:
  ResourceManager *resourceManager;

public:
  /**
   * Shop Scene constructor with required resourceManager reference
   *
   * @param resManager the ResourceManager that controls internally and externally saved resources
   */
  MainMenuScene(ResourceManager &resManager);

  /**
   * Render the MainMenuScene.
   *
   * @param renderer the Renderer that controls the window rendering and camera
   */
  void render(Renderer &renderer);

  /**
   * Progress the animation and input effects of the MainMenuScene
   * @param input the InputHandler used to handle keyboard and mouse input from the player
   * @param renderer the Renderer that controls the window rendering and camera
   */
  void physicsStep(InputHandler &input, Renderer &renderer);
};

#endif // MAINMENUSCENE_H
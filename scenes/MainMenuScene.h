#ifndef MAINMENUSCENE_H
#define MAINMENUSCENE_H

#include "../entities/TextElement.h"

#include "../Renderer.h"
#include "../ResourceManager.h"
#include "../InputHandler.h"

class MainMenuScene
{
private:
  const std::string legalBoilerplate = "Poppy's Scuttle Slugging isn't endorsed by Riot Games and doesn't reflect the views or opinions of Riot Games or anyone officially involved in producing or managing Riot Games properties. Riot Games, and all associated properties are trademarks or registered trademarks of Riot Games, Inc.";
  ResourceManager *resourceManager;
  std::unordered_map<std::string, UIElement::ButtonData> buttons;

  /**
   * Handle any button presses that occur.
   *
   * @param input the InputHandler used to handle keyboard and mouse input from the player
   * @param renderer the Renderer that controls the window rendering and camera
   */
  void handleButtons(InputHandler &input, Renderer &renderer);

  void renderLegalBoilerplate(Renderer &renderer);

public:
  /**
   * MainMenuScene constructor with required resourceManager reference
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
   *
   * @param input the InputHandler used to handle keyboard and mouse input from the player
   * @param renderer the Renderer that controls the window rendering and camera
   */
  void physicsStep(InputHandler &input, Renderer &renderer);
};

#endif // MAINMENUSCENE_H